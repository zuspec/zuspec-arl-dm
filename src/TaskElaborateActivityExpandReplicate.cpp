/*
 * TaskElaborateActivityExpandReplicate.cpp
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
#include "vsc/impl/DebugMacros.h"
#include "arl/impl/CopyVisitor.h"
#include "TaskElaborateActivityExpandReplicate.h"
#include "TaskElaborateActivitySelectReplicateSizes.h"


namespace arl {


TaskElaborateActivityExpandReplicate::TaskElaborateActivityExpandReplicate(
    IContext *ctxt) : m_ctxt(ctxt) {
    DEBUG_INIT("TaskElaborateActivityExpandReplicate", m_ctxt->getDebugMgr());

}

TaskElaborateActivityExpandReplicate::~TaskElaborateActivityExpandReplicate() {

}

IModelActivityScope *TaskElaborateActivityExpandReplicate::elab(
    vsc::IRandState         *randstate,
    IModelActivityScope     *root) {
    DEBUG_ENTER("elab");
    m_result = IModelActivityScopeUP(
        m_ctxt->mkModelActivityScope(ModelActivityScopeT::Sequence));
    m_scope_s.push_back(m_result.get());

    root->accept(m_this);

    DEBUG_LEAVE("elab");
    return m_result.release();
}

void TaskElaborateActivityExpandReplicate::visitModelActivityScope(
    IModelActivityScope *a) {
    DEBUG_ENTER("visitModelActivityScope %d", a->getType());
    // Construct a duplicate scope to contain the elements inside
    IModelActivityScope *scope = m_ctxt->mkModelActivityScope(a->getType());
    m_scope_s.back()->addActivity(scope, true);
    m_scope_s.push_back(scope);
    for (std::vector<IModelActivity *>::const_iterator
        it=a->activities().begin();
        it!=a->activities().end(); it++) {
        (*it)->accept(m_this);
    }
    m_scope_s.pop_back();
    DEBUG_LEAVE("visitModelActivityScope");
}

void TaskElaborateActivityExpandReplicate::visitModelActivityTraverse(
    IModelActivityTraverse *a) {
    DEBUG_ENTER("visitModelActivityTraverse");
    // Just gets added 

    if (a->getTarget()->isCompound()) {
        // We need to clone a compound activity, since we will be
        // changing the contained compound activity

        IModelActivityScope *scope = m_ctxt->mkModelActivityScope(
            a->getTarget()->getActivity()->getType());
        IModelActivityTraverse *traverse = m_ctxt->mkModelActivityTraverse(
            a->getTarget(),
            a->getWithC(),
            false,
            scope,
            true);
        m_scope_s.back()->addActivity(traverse, true);
        m_scope_s.push_back(scope);
        a->getTarget()->getActivity()->accept(m_this);
        m_scope_s.pop_back();
    } else {
        m_scope_s.back()->addActivity(a, false);
    }
    DEBUG_LEAVE("visitModelActivityTraverse");
}

void TaskElaborateActivityExpandReplicate::visitModelActivityReplicate(
    IModelActivityReplicate *a) {
    DEBUG_ENTER("visitModelActivityReplicate");

    // IModelActivityScope *scope = m_ctxt->mkModelActivityScope(a->getType());
    // m_scope_s.back()->addActivity(scope, true);
    // m_scope_s.push_back(scope);
    // for (std::vector<IModelActivity *>::const_iterator
    //     it=a->activities().begin();
    //     it!=a->activities().end(); it++) {
    //     (*it)->accept(m_this);
    // }
    // m_scope_s.pop_back();
    CopyVisitor cv(m_ctxt);

    DEBUG("Replicate size: %lld\n", a->getCountField()->val()->val_u());

    // Copy any local fields, skipping __count and __index
    for (uint32_t i=2; i<a->fields().size(); i++) {
        m_scope_s.back()->addField(
            cv.copyT<vsc::IModelField>(a->fields().at(i).get()));
    }

    // TODO: need to replace count/index with values

    // TODO: establish the replicate range
    int32_t count = 2;

    for (int32_t i=0; i<count; i++) {

        // Sub-elements must be replicated N times and added to the
        // containing scope
        for (std::vector<IModelActivity *>::const_iterator
            it=a->activities().begin();
            it!=a->activities().end(); it++) {

            // TODO: Ensure that we use the fixed-value field
            // when referring to the index
        
            // TODO: Likely need a stack of these variables

            DEBUG("copying activity");
            m_scope_s.back()->addActivity(cv.copyT<IModelActivity>(*it), true);
        }
    }

    DEBUG_LEAVE("visitModelActivityReplicate");
}

vsc::IDebug *TaskElaborateActivityExpandReplicate::m_dbg = 0;

}
