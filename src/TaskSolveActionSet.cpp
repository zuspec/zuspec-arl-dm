/*
 * TaskSolveActionSet.cpp
 *
 * Copyright 2022 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author:
 */
#include "arl/IDataTypeAction.h"
#include "arl/IDataTypeComponent.h"
#include "arl/IModelFieldPool.h"
#include "vsc/impl/TaskUnrollModelFieldRefConstraints.h"
#include "DebugMacros.h"
#include "TaskSolveActionSet.h"
#include "TaskIsDataTypeFlowObj.h"


namespace arl {

TaskSolveActionSet::TaskSolveActionSet(
    IContext                *ctxt,
    IModelFieldComponent    *comp) : m_ctxt(ctxt), m_comp(comp) {
    DEBUG_INIT("TaskSolveActionSet");
    m_action_data = 0;
}

TaskSolveActionSet::~TaskSolveActionSet() {

}

bool TaskSolveActionSet::solve(
    const std::vector<IModelActivityTraverse *> &traversals) {
    DEBUG_ENTER("solve - %d traversals", traversals.size());
    bool ret = true;

    m_all_comp_m.clear();
    m_all_comp_l.clear();

    // Initialize the action-data collection
    m_action_data_l.clear();
    for (std::vector<IModelActivityTraverse *>::const_iterator
        it=traversals.begin(); 
        it!=traversals.end(); it++) {
        m_action_data_l.push_back(ActionData());
    }

    build_comp_map(traversals);

    // Collect claims
    // Out goal is to build a per-type map of all resources
    // and their extents (ie what components provide them)
    //
    // comp_id -> [range]
    // 
    for (std::vector<IModelActivityTraverse *>::const_iterator
        it=traversals.begin(); 
        it!=traversals.end(); it++) {
        (*it)->getTarget()->getDataType()->accept(m_this);
    }

    // Now that we've built the proper data, process the objects
    for (uint32_t i=0; i<traversals.size(); i++) {
        m_action_data = &m_action_data_l.at(i);
        traversals.at(i)->getTarget()->accept(m_this);
    }

    // TODO: Collect fields and constraints to solve for

    // Assign action refs if we were able to solve properly
    if (ret) {
        for (std::vector<ActionData>::const_iterator
            action_it=m_action_data_l.begin();
            action_it!=m_action_data_l.end(); action_it++) {
            for (std::vector<RefSelPairT>::const_iterator
                ref_sel_it=action_it->m_refs.begin();
                ref_sel_it!=action_it->m_refs.end(); ref_sel_it++) {
                ref_sel_it->first->setRef(ref_sel_it->second->getSelected());
            }
        }
    }

    DEBUG_LEAVE("solve - ret=%d", ret);
    return ret;    
}

void TaskSolveActionSet::build_comp_map(
    const std::vector<IModelActivityTraverse *> &traversals) {
    // Build a list of all component contexts and the
    // per-action specifics

    for (uint32_t i=0; i<traversals.size(); i++) {
        IModelActivityTraverse *tr = traversals.at(i);
        // For each action instance, ask where its type can run
        IDataTypeAction *action_t = tr->getTarget()->getDataTypeT<IDataTypeAction>();
        IDataTypeComponent *comp_t = action_t->getComponentType();
        const std::vector<IModelFieldComponent *> &comp_l = 
            m_comp->getCompMap()->getSubContexts(comp_t);
        
        // Now, we need to merge these with the global list, and 
        // capture which are needed on a per-action basis
        for (std::vector<IModelFieldComponent *>::const_iterator
            c_it=comp_l.begin();
            c_it!=comp_l.end(); c_it++) {
            AllCompMapT::const_iterator it=m_all_comp_m.find(*c_it);
            uint32_t idx;

            if (it == m_all_comp_m.end()) {
                idx = m_all_comp_l.size();
                m_all_comp_l.push_back(*c_it);
                m_all_comp_m.insert({*c_it, idx});
            } else {
                idx = it->second;
            }

            m_action_data_l.at(i).comp_ctxt_l.push_back(idx);
        }
    }
}

void TaskSolveActionSet::visitModelFieldRef(vsc::IModelFieldRef *f) {
    DEBUG_ENTER("visitModelFieldRef %s", f->name().c_str());
    if (TaskIsDataTypeFlowObj::test(f->getDataType())) {
        IDataTypeFlowObj *fo_t = f->getDataTypeT<IDataTypeFlowObj>();
        DEBUG("Is a DataTypeFlowObj %d", fo_t->kind());

        if (fo_t->kind() == FlowObjKindE::Resource) {
            // Build a selector to implement assignment of this resource
            ResTypeMapT::iterator res_t = m_res_type_m.find(f->getDataType());
            std::vector<vsc::IModelField *> candidates;

            uint32_t comp_ctxt_idx = 0;
            uint32_t rsrc_idx = 0;
            for (std::vector<std::pair<int32_t,int32_t>>::const_iterator
                it=res_t->second.m_comp_sz_l.begin();
                it!=res_t->second.m_comp_sz_l.end(); it++) {
                bool valid = (m_action_data->comp_ctxt_l.at(comp_ctxt_idx) == it->first);

                for (uint32_t i=0; i<it->second; i++) {
                    if (valid) {
                        candidates.push_back(res_t->second.m_resource_l.at(rsrc_idx));
                    } else {
                        candidates.push_back(0);
                    }
                    rsrc_idx++;
                }

                if (valid) {
                    comp_ctxt_idx++;
                }
            }

            vsc::ModelFieldRefConstraintData *data = 
                vsc::TaskUnrollModelFieldRefConstraints(m_ctxt).build(
                    f, 
                    candidates,
                    {},
                    m_constraints);
            
            // Store the data on the action as well as in the 
            bool is_lock = true; // TODO:

            if (is_lock) {
                res_t->second.m_lock_claims.push_back(data);
            } else {
                res_t->second.m_share_claims.push_back(data);
            }

            m_action_data->m_refs.push_back({f, vsc::ModelFieldRefConstraintDataUP(data)});
            



        } else {
            // TODO:

        }
    }

    DEBUG_LEAVE("visitModelFieldRef %s", f->name().c_str());
}

void TaskSolveActionSet::visitTypeFieldClaim(ITypeFieldClaim *f) {
    DEBUG_ENTER("visitTypeFieldClaim %s", f->name().c_str());
    vsc::IDataType *claim_t = f->getDataType();

    // - Process every component instance that we have
    // - If the component instance has a mapping for ResType, add it
    // 
    ResTypeMapT::iterator it = m_res_type_m.find(claim_t);

    if (it == m_res_type_m.end()) {
        it = m_res_type_m.insert({claim_t, ResourceClaimData()}).first;

        for (uint32_t comp_idx=0; comp_idx<m_all_comp_l.size(); comp_idx++) {
            IModelFieldPool *pool = m_all_comp_l.at(comp_idx)->getCompMap()->getPool(f);

            if (pool) {
                it->second.m_comp_sz_l.push_back({comp_idx, pool->getObjects().size()});

                for (std::vector<vsc::IModelFieldUP>::const_iterator
                    o_it=pool->getObjects().begin();
                    o_it!=pool->getObjects().end(); o_it++) {
                    it->second.m_resource_l.push_back(o_it->get());
                }
            }
        }
    }

    DEBUG_LEAVE("visitTypeFieldClaim");
}

void TaskSolveActionSet::visitTypeFieldInOut(ITypeFieldInOut *f) {

}

}
