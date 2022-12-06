/*
 * ActivityScheduleData.cpp
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
#include "arl/IDataTypeResource.h"
#include "arl/IModelFieldClaim.h"
#include "vsc/IModelFieldType.h"
#include "ActivityScheduleData.h"
#include "vsc/impl/DebugMacros.h"

namespace arl {


ActivityScheduleData::ActivityScheduleData(
    IContext                    *ctxt,
    IModelComponentTreeData     *comp_data) : m_ctxt(ctxt), m_comp_data(comp_data) {
    DEBUG_INIT("ActivityScheduleData", ctxt->getDebugMgr());

}

ActivityScheduleData::~ActivityScheduleData() {

}

void ActivityScheduleData::initRefSelectors() {
    for (std::vector<vsc::IRefSelector *>::const_iterator
        it=m_buffer_sel_l.begin();
        it!=m_buffer_sel_l.end(); it++) {
        (*it)->init(m_ctxt);
    }
    for (std::vector<vsc::IRefSelector *>::const_iterator
        it=m_resource_sel_l.begin();
        it!=m_resource_sel_l.end(); it++) {
        (*it)->init(m_ctxt);
    }
    for (std::vector<vsc::IRefSelector *>::const_iterator
        it=m_stream_sel_l.begin();
        it!=m_stream_sel_l.end(); it++) {
        (*it)->init(m_ctxt);
    }
    for (std::vector<ActionDataUP>::const_iterator
        it=m_action_l.begin();
        it!=m_action_l.end(); it++) {
        (*it)->comp_ref_sel->init(m_ctxt);
    }
}

void ActivityScheduleData::getSelectorsConstraints(
        std::vector<vsc::IRefSelector *>        &refs,
        std::vector<vsc::IModelConstraint *>    &constraints) {
    // TODO: only get selectors for refs not yet resolved?
    // TODO: get soft validity constraint?
    for (std::vector<vsc::IRefSelector *>::const_iterator
        it=m_buffer_sel_l.begin();
        it!=m_buffer_sel_l.end(); it++) {
        refs.push_back(*it);
        constraints.push_back((*it)->getValidSoftC());
    }
    for (std::vector<vsc::IRefSelector *>::const_iterator
        it=m_resource_sel_l.begin();
        it!=m_resource_sel_l.end(); it++) {
        refs.push_back(*it);
        constraints.push_back((*it)->getValidSoftC());
    }
    for (std::vector<vsc::IRefSelector *>::const_iterator
        it=m_stream_sel_l.begin();
        it!=m_stream_sel_l.end(); it++) {
        refs.push_back(*it);
        // Insist on valid resource assignments
        constraints.push_back((*it)->getValidC());
    }
    for (std::vector<ActionDataUP>::const_iterator
        it=m_action_l.begin();
        it!=m_action_l.end(); it++) {
        refs.push_back((*it)->comp_ref_sel.get());
        // Insist on valid component context
        constraints.push_back((*it)->comp_ref_sel->getValidC());
    }
    for (std::vector<vsc::IModelConstraintUP>::const_iterator
        it=m_constraints.begin();
        it!=m_constraints.end(); it++) {
        constraints.push_back(it->get());
    }
}


ActivityScheduleData::ActionTraversalData *ActivityScheduleData::getTraversal(IModelActivityTraverse *t) {
    std::unordered_map<IModelActivityTraverse *, int32_t>::iterator it;

    if ((it=m_traversal_id_m.find(t)) != m_traversal_id_m.end()) {
        return m_traversal_l.at(it->second).get();
    } else {
        return 0;
    }
}

ActivityScheduleData::ActionTraversalData *ActivityScheduleData::addTraversal(
    IModelFieldAction       *parent,
    IModelActivityTraverse  *traversal,
    vsc::IModelExpr         *cond) {

    ActivityScheduleData::ActionTraversalData *ret = 0;
    DEBUG_ENTER("addTraversal");
    std::unordered_map<IModelActivityTraverse *, int32_t>::iterator it;

    if ((it=m_traversal_id_m.find(traversal)) == m_traversal_id_m.end()) {
        // See if the action exists
        std::unordered_map<IModelFieldAction *, int32_t>::iterator a_it;

        if ((a_it=m_action_id_m.find(traversal->getTarget())) == m_action_id_m.end()) {
            a_it = m_action_id_m.insert({traversal->getTarget(), m_action_l.size()}).first;
            ActionData *a_data = new ActionData();
            a_data->action = traversal->getTarget();
            IDataTypeComponent *comp_t = traversal->getTarget()->getDataTypeT<IDataTypeAction>()->getComponentType();
            a_data->comp_ref_sel = vsc::IRefSelectorUP(m_ctxt->mkRefSelector(
                traversal->getTarget()->getFieldT<vsc::IModelFieldRef>(0),
                m_comp_data->getCompTypeInsts(comp_t)));
            m_action_l.push_back(ActionDataUP(a_data));
        }

        it = m_traversal_id_m.insert({traversal, m_traversal_l.size()}).first;
        ActionTraversalData *tr_data = new ActionTraversalData();
        tr_data->action = m_action_l.at(a_it->second).get();
        m_traversal_l.push_back(ActionTraversalDataUP(tr_data));
        // TODO: parent
        m_traversal_l.back()->traversal = traversal;
    }


    DEBUG_LEAVE("addTraversal action=%p", m_traversal_l.at(it->second)->action);
    return m_traversal_l.at(it->second).get();
};

ActivityScheduleData::CheckPoint ActivityScheduleData::checkpoint() {

}

void ActivityScheduleData::restore(const ActivityScheduleData::CheckPoint &cp) {

}

vsc::IRefSelector *ActivityScheduleData::getRefSelector(vsc::IModelFieldRef *ref) {
    std::unordered_map<vsc::IModelFieldRef *,vsc::IRefSelectorUP>::const_iterator it;
    
    if ((it=m_ref_selector_m.find(ref)) != m_ref_selector_m.end()) {
        return it->second.get();
    } else {
        return 0;
    }
}

vsc::IRefSelector *ActivityScheduleData::addRefSelector(
        vsc::IModelFieldRef         *ref,
        FlowObjKindE                kind) {
    // Find (and/or add) the data for this ref type
    FlowObjTypeM::iterator it = m_objtype_m.find(ref->getDataType());

    if (it == m_objtype_m.end()) {
        it = m_objtype_m.insert({ref->getDataType(), ObjData()}).first;
    }

    vsc::IRefSelector *ret = m_ctxt->mkRefSelector(
        ref,
        it->second.obj_l);
    
    m_ref_selector_m.insert({ref, vsc::IRefSelectorUP(ret)});

    switch (ref->getDataTypeT<IDataTypeFlowObj>()->kind()) {
        case FlowObjKindE::Buffer: m_buffer_sel_l.push_back(ret); break;
//        case FlowObjKindE::Resource: m_resource_sel_l.push_back(ret); break;
        case FlowObjKindE::Stream: m_stream_sel_l.push_back(ret); break;
        default: fprintf(stdout, "Error: unhandled flow-object kind %d\n", 
            ref->getDataTypeT<IDataTypeFlowObj>()->kind());
    }

    return ret;
}

int32_t ActivityScheduleData::getFlowObjId(vsc::IModelField *obj) {
    FlowObjTypeM::iterator it = m_objtype_m.find(obj->getDataType());

    if (it == m_objtype_m.end()) {
        it = m_objtype_m.insert({obj->getDataType(), ObjData()}).first;
    }

    // Check to see if a flow-object exists for this field
    std::unordered_map<vsc::IModelField *, int32_t>::const_iterator i_it;

    if ((i_it=it->second.obj2id_m.find(obj)) != it->second.obj2id_m.end()) {
        return i_it->second;
    } else {
        return -1;
    }
}

int32_t ActivityScheduleData::addFlowObj(vsc::IModelField *obj) {
    FlowObjTypeM::iterator it = m_objtype_m.find(obj->getDataType());

    if (it == m_objtype_m.end()) {
        it = m_objtype_m.insert({obj->getDataType(), ObjData()}).first;
    }

    std::unordered_map<vsc::IModelField *, int32_t>::const_iterator i_it;

    if ((i_it=it->second.obj2id_m.find(obj)) == it->second.obj2id_m.end()) {
        int32_t id = it->second.obj_l.size();
        it->second.obj_l.push_back(obj);
        i_it = it->second.obj2id_m.insert({obj, id}).first;
    }

    return i_it->second;
}

ActivityScheduleData::ClaimData *ActivityScheduleData::getClaim(
    ActivityScheduleData::ActionData    *action,
    IModelFieldClaim                    *f) {
    DEBUG_ENTER("getClaim");
    std::unordered_map<IModelFieldClaim *, ActivityScheduleData::ClaimDataUP>::iterator it;

    if ((it=action->claim_m.find(f)) == action->claim_m.end()) {
        ActivityScheduleData::ClaimData *c = new ActivityScheduleData::ClaimData();
        c->selector = vsc::IRefSelectorUP(m_ctxt->mkRefSelector(
            f,
            m_comp_data->getResObjects(f->getDataTypeT<IDataTypeResource>())
        ));
        DEBUG("Create new ref %p", c->selector.get());

        // TODO: Build per-action constraints since these are invariant

        it = action->claim_m.insert({f, ActivityScheduleData::ClaimDataUP(c)}).first;
        m_resource_sel_l.push_back(c->selector.get());
    }
    
    DEBUG_LEAVE("getClaim");
    return it->second.get();
}

void ActivityScheduleData::addConstraint(vsc::IModelConstraint *c) {
    m_constraints.push_back(vsc::IModelConstraintUP(c));
};

vsc::IDebug *ActivityScheduleData::m_dbg = 0;

}
