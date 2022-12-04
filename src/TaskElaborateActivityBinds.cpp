/*
 * TaskElaborateActivityBinds.cpp
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
#include "arl/impl/ModelBuildContext.h"
#include "arl/impl/TaskVisitModelFieldInOut.h"
#include "arl/impl/TaskVisitModelFieldClaim.h"
#include "vsc/impl/DebugMacros.h"
#include "TaskElaborateActivityBinds.h"


namespace arl {


TaskElaborateActivityBinds::TaskElaborateActivityBinds(
    IContext *ctxt) : m_ctxt(ctxt) {
    m_sched_data = 0;
    DEBUG_INIT("TaskElaborateActivityBinds", ctxt->getDebugMgr());

}

TaskElaborateActivityBinds::~TaskElaborateActivityBinds() {

}

bool TaskElaborateActivityBinds::elab(
    ActivityScheduleData    *sched_data,
    IModelActivity          *activity) {
    DEBUG_ENTER("elab");
    m_sched_data = sched_data;

    activity->accept(m_this);

    // TODO: Foreach action
    //         foreach claim
    //           Add comp_id -> claim_id_range constraint
    //         foreach ref
    //           Add comp_id -> pool_id constraint

    DEBUG_LEAVE("elab");
    return true;
}

void TaskElaborateActivityBinds::visitModelActivityBind(IModelActivityBind *a) {
    // TODO: capture bind relationships along with condition (if applicable)

}

void TaskElaborateActivityBinds::visitModelActivityParallel(IModelActivityParallel *a) {
    DEBUG_ENTER("visitModelActivityParallel");
    processActivityParallel(a);
    DEBUG_LEAVE("visitModelActivityParallel");
}

void TaskElaborateActivityBinds::visitModelActivitySchedule(IModelActivitySchedule *a) {
    DEBUG_ENTER("visitModelActivitySchedule");
    processActivitySchedule(a);

    // At root schedule only ...
    // - Collect all actions within the region
    // - Build and initialize relation-pair array
    // - Add in fixed-schedule information
    // - Add binds based on 

    DEBUG_LEAVE("visitModelActivitySchedule");
}

void TaskElaborateActivityBinds::visitModelActivitySequence(IModelActivitySequence *a) {
    DEBUG_ENTER("visitModelActivitySequence");
    processActivitySequence(a);
    DEBUG_LEAVE("visitModelActivitySequence");
}

void TaskElaborateActivityBinds::visitModelActivityScope(IModelActivityScope *a) {
    DEBUG_ENTER("visitActivityScope %d", a->getType());
    switch (a->getType()) {
        case ModelActivityScopeT::Parallel: 
            processActivityParallel(a);
            break;
        case ModelActivityScopeT::Schedule: 
            processActivitySchedule(a);
            break;
        case ModelActivityScopeT::Sequence: 
            processActivitySequence(a);
            break;
        default:
            DEBUG("Error: unknown scope type");
    }
    DEBUG_LEAVE("visitActivityScope");
}

void TaskElaborateActivityBinds::visitModelActivityTraverse(IModelActivityTraverse *a) {
    DEBUG_ENTER("visitModelActivityTraverse %s", a->getTarget()->name().c_str());

    ActivityScheduleData::ActionTraversalData *td = m_sched_data->getTraversal(a);

    // Add if it doesn't already exist
    if (!td) {
        // TODO: create a condition if required
        IModelFieldAction *parent = 0;
        vsc::IModelExpr *cond = 0;

        if (m_traverse_s.size() > 0) {
            parent = m_traverse_s.back()->traversal->getTarget();
        }

        td = m_sched_data->addTraversal(
            parent,
            a,
            cond);
    }

    m_traverse_s.push_back(td);

    // Push a scope for collecting resources
    m_resource_s.push_back(ResourceClaimM());
    TaskVisitModelFieldClaim(
        [&](IModelFieldClaim *f) { processClaim(f); }
        ).visit(a->getTarget());
    
    const ResourceClaimM &last = m_resource_s.back();

    // Note: these constraints are really per-type, and shouldn't need
    // to be created during traversal analysis
    for (std::vector<vsc::IDataType *>::const_iterator
        dt_it=last.types.begin();
        dt_it!=last.types.end(); dt_it++) {

        std::unordered_map<vsc::IDataType *, ResourceClaimType>::const_iterator l_it;
        l_it=last.claims.find(*dt_it);

        // TODO: add lock <-> lock exclusion constraints
        for (uint32_t i=0; i<l_it->second.lock.size(); i++) {
            for (uint32_t j=i+1; j<l_it->second.lock.size(); j++) {
                DEBUG("Add action-specific lock <-> lock constraints");
                m_sched_data->addConstraint(
                    m_ctxt->mkModelConstraintExpr(
                        m_ctxt->mkModelExprBin(
                            m_ctxt->mkModelExprFieldRef(l_it->second.lock.at(i)->getSelector()),
                            vsc::BinOp::Ne,
                            m_ctxt->mkModelExprFieldRef(l_it->second.lock.at(j)->getSelector()))));
            }
        }

        // TODO: add lock <-> share exclusion constraints
        for (std::vector<vsc::IRefSelector *>::const_iterator
            ll_it=l_it->second.lock.begin();
            ll_it!=l_it->second.lock.end(); ll_it++) {
            for (std::vector<vsc::IRefSelector *>::const_iterator
                ls_it=l_it->second.share.begin();
                ls_it!=l_it->second.share.end(); ls_it++) {
                DEBUG("TODO: Add action-specific lock <-> share constraints");
                m_sched_data->addConstraint(
                    m_ctxt->mkModelConstraintExpr(
                        m_ctxt->mkModelExprBin(
                            m_ctxt->mkModelExprFieldRef((*ll_it)->getSelector()),
                            vsc::BinOp::Ne,
                            m_ctxt->mkModelExprFieldRef((*ls_it)->getSelector()))));
            }
        }
    }

    // Propagate up the stack if someone else
    // has signaled an interest
    if (m_resource_s.size() > 1) {
        propagateResources(
            m_resource_s.at(m_resource_s.size()-2),
            m_resource_s.back());
    }

//    for ()

    // Find/add a traversal entry
    // Find/add an action entry

    // Process input references first
    TaskVisitModelFieldInOut([&](IModelFieldInOut *f) { 
        if (f->isInput()) {
            processRefInput(f);
        }
    }).visit(a->getTarget());

    // Now, 

//    if (m_traverse_s.size()) {
//        parent = m_traverse_s.back()->getTarget();
//    }


//    m_sched_data->addTraversal(parent, a, cond);

    if (a->getActivity()) {
        DEBUG_ENTER("visitModelActivityTraverse --> visitActivity");
        a->getActivity()->accept(m_this);
        DEBUG_LEAVE("visitModelActivityTraverse <-- visitActivity");
    }
    m_traverse_s.pop_back();
    m_resource_s.pop_back();

    DEBUG_LEAVE("visitModelActivityTraverse %s", a->getTarget()->name().c_str());
}

void TaskElaborateActivityBinds::processClaim(IModelFieldClaim *f) {
    DEBUG_ENTER("processClaim");

    std::unordered_map<vsc::IDataType *, ResourceClaimType>::iterator it;

    if ((it=m_resource_s.back().claims.find(f->getDataType())) == m_resource_s.back().claims.end()) {
        it = m_resource_s.back().claims.insert({f->getDataType(), ResourceClaimType()}).first;
        m_resource_s.back().types.push_back(f->getDataType());
    }

    // Obtain 
    ActivityScheduleData::ClaimData *claim = m_sched_data->getClaim(
        m_traverse_s.back()->action, f);

    if (f->isLock()) {
        DEBUG("Add lock %p", claim->selector.get());
        it->second.lock.push_back(claim->selector.get());
    } else {
        it->second.share.push_back(claim->selector.get());
    }

    DEBUG_LEAVE("processClaim");
}

void TaskElaborateActivityBinds::processRefInput(IModelFieldInOut *f) {
    DEBUG_ENTER("processRefInput");
    switch (f->getDataTypeT<IDataTypeFlowObj>()->kind()) {
        case FlowObjKindE::Buffer:
            break;
    }

    // Determine what kind of object this is

    // Add available object indices to the corresponding ref's 

    DEBUG_LEAVE("processRefInput");
}

void TaskElaborateActivityBinds::processRefOutput(IModelFieldInOut *f) {
    DEBUG_ENTER("processRefOutput");
    // Determine what kind of object this is 

    // Create an object if this field isn't already populated
    int32_t id;
    if (!f->getRef()) {
        arl::ModelBuildContext build_ctxt(m_ctxt);
        f->setRef(f->getDataType()->mkRootField(&build_ctxt, f->name(), false));

        // Add this object to the collection
        id = m_sched_data->addFlowObj(f->getRef());
    } else {
        id = m_sched_data->getFlowObjId(f->getRef());
    }

    switch (f->getDataTypeT<IDataTypeFlowObj>()->kind()) {

    }

    // 

    DEBUG_LEAVE("processRefOutput");
}

void TaskElaborateActivityBinds::processActivityParallel(IModelActivityScope *a) {
    DEBUG_ENTER("processActivityParallel");
    // TODO: If any branch has a schedule prior to any action, then we should 
    // treat the parallel as if it were a schedule with some specific
    // relationships between branches.
    // 
    // Note: this is from the perspective of binding.

    // Collect up stream ouputs from first actions

    // Foreach branch:
    //     Push temp collector for buffer/state encountered on this branch
    //     Visit branch
    //     Pop temp collectors for buffer/state encountered on this branch
    // Incorporate buffer/state in containing object state
    ResourceClaimM combined_claim_data;

    for (std::vector<IModelActivity *>::const_iterator
        it=a->activities().begin();
        it!=a->activities().end(); it++) {
        m_resource_s.push_back(ResourceClaimM());

        (*it)->accept(m_this);

        if (it != a->activities().begin()) {
            // Add new resource constraints to the action

            // Iterate through the types introduced by this 
            for (std::vector<vsc::IDataType *>::const_iterator
                rt_it=m_resource_s.back().types.begin();
                rt_it!=m_resource_s.back().types.end(); rt_it++) {
                DEBUG("Checking resource type %p from parallel branch", *rt_it);
                std::unordered_map<vsc::IDataType *, ResourceClaimType>::const_iterator
                    ex_rt_it = combined_claim_data.claims.find(*rt_it);
                if (ex_rt_it != combined_claim_data.claims.end()) {
                    // Ensure that no two locks between the two sets claims the same resource
                    std::unordered_map<vsc::IDataType *, ResourceClaimType>::const_iterator
                        n_rt_it = m_resource_s.back().claims.find(*rt_it); 

                    // Add lock <-> lock constraints
                    for (std::vector<vsc::IRefSelector *>::const_iterator
                        n_it=n_rt_it->second.lock.begin();
                        n_it!=n_rt_it->second.lock.end(); n_it++) {
                        for (std::vector<vsc::IRefSelector *>::const_iterator
                            e_it=ex_rt_it->second.lock.begin();
                            e_it!=ex_rt_it->second.lock.end(); e_it++) {
                            DEBUG("Add lock <-> lock constraint");
                            m_sched_data->addConstraint(
                                m_ctxt->mkModelConstraintExpr(
                                    m_ctxt->mkModelExprBin(
                                        m_ctxt->mkModelExprFieldRef((*n_it)->getSelector()),
                                        vsc::BinOp::Ne,
                                        m_ctxt->mkModelExprFieldRef((*e_it)->getSelector()))));
                        }
                    }

                    // Add lock <-> share constraints
                    for (std::vector<vsc::IRefSelector *>::const_iterator
                        n_it=n_rt_it->second.lock.begin();
                        n_it!=n_rt_it->second.lock.end(); n_it++) {
                        for (std::vector<vsc::IRefSelector *>::const_iterator
                            e_it=ex_rt_it->second.share.begin();
                            e_it!=ex_rt_it->second.share.end(); e_it++) {
                            DEBUG("Add lock <-> share constraint");
                            m_sched_data->addConstraint(
                                m_ctxt->mkModelConstraintExpr(
                                    m_ctxt->mkModelExprBin(
                                        m_ctxt->mkModelExprFieldRef((*n_it)->getSelector()),
                                        vsc::BinOp::Ne,
                                        m_ctxt->mkModelExprFieldRef((*e_it)->getSelector()))));
                        }
                    }

                    /* Isn't this a duplicate?
                    // Add share <-> lock constraints
                    for (std::vector<vsc::IRefSelector *>::const_iterator
                        n_it=n_rt_it->second.share.begin();
                        n_it!=n_rt_it->second.share.end(); n_it++) {
                        for (std::vector<vsc::IRefSelector *>::const_iterator
                            e_it=ex_rt_it->second.lock.begin();
                            e_it!=ex_rt_it->second.lock.end(); e_it++) {
                            DEBUG("TODO: add share <-> lock constraint");
                        }
                    }
                     */
                }
            }
        }

        // Incorporate in the aggregate set
        propagateResources(combined_claim_data, m_resource_s.back());

        m_resource_s.pop_back();
    }

    DEBUG_LEAVE("processActivityParallel");
}

void TaskElaborateActivityBinds::processActivitySchedule(IModelActivityScope *a) {
    DEBUG_ENTER("processActivitySchedule");
    for (std::vector<IModelActivity *>::const_iterator
        it=a->activities().begin();
        it!=a->activities().end(); it++) {
        (*it)->accept(m_this);
    }
    DEBUG_LEAVE("processActivitySchedule");
}

void TaskElaborateActivityBinds::processActivitySequence(IModelActivityScope *a) {
    DEBUG_ENTER("processActivitySequence");
    // Progress any refs/claims on this 

    // Map <FlowOBjT> -> List<Index>
    // 

    for (std::vector<IModelActivity *>::const_iterator
        it=a->activities().begin();
        it!=a->activities().end(); it++) {
        (*it)->accept(m_this);
    }

    DEBUG_LEAVE("processActivitySequence");
}

void TaskElaborateActivityBinds::propagateResources(
        ResourceClaimM              &dst,
        const ResourceClaimM        &src) {
    for (std::vector<vsc::IDataType *>::const_iterator
        rt_it=src.types.begin();
        rt_it!=src.types.end(); rt_it++) {
        std::unordered_map<vsc::IDataType *, ResourceClaimType>::iterator cc_it;
        std::unordered_map<vsc::IDataType *, ResourceClaimType>::const_iterator bc_it;

        bc_it = src.claims.find(*rt_it);

        if ((cc_it=dst.claims.find(*rt_it)) == dst.claims.end()) {
            cc_it = dst.claims.insert({*rt_it, ResourceClaimType()}).first;
            dst.types.push_back(*rt_it);
        }

        for (std::vector<vsc::IRefSelector *>::const_iterator
            cl_it=bc_it->second.lock.begin();
            cl_it!=bc_it->second.lock.end(); cl_it++) {
            DEBUG("Adding lock %p", *cl_it);
            cc_it->second.lock.push_back(*cl_it);
        }

        for (std::vector<vsc::IRefSelector *>::const_iterator
            cl_it=bc_it->second.share.begin();
            cl_it!=bc_it->second.share.end(); cl_it++) {
            cc_it->second.share.push_back(*cl_it);
        }
    }
}

vsc::IDebug *TaskElaborateActivityBinds::m_dbg = 0;

}
