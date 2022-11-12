/*
 * TaskElaborateActivitySelectReplicateSizes.cpp
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
#include "vsc/impl/PrettyPrinter.h"
#include "TaskElaborateActivitySelectReplicateSizes.h"


namespace arl {


TaskElaborateActivitySelectReplicateSizes::TaskElaborateActivitySelectReplicateSizes(
    IContext *ctxt) : m_ctxt(ctxt) {
    
    DEBUG_INIT("TaskElaborateActivitySelectReplicateSizes", m_ctxt->getDebugMgr());

}

TaskElaborateActivitySelectReplicateSizes::~TaskElaborateActivitySelectReplicateSizes() {

}

bool TaskElaborateActivitySelectReplicateSizes::eval(
    vsc::IRandState         *randstate,
    IModelActivity          *root) {
    root->accept(m_this);

    // Now that we have the fields, solve all at once to arrive at a
    // consistent result
    vsc::ICompoundSolverUP solver(m_ctxt->mkCompoundSolver());

    DEBUG("Fields: %d ; Constraints: %d", m_count_fields.size(), m_constraints.size());

    bool ret = solver->solve(
        randstate,
        m_count_fields,
        m_constraints,
        vsc::SolveFlags::Randomize 
        | vsc::SolveFlags::RandomizeDeclRand
        | vsc::SolveFlags::RandomizeTopFields
    );

    return ret;
}

void TaskElaborateActivitySelectReplicateSizes::visitModelActivityReplicate(
    IModelActivityReplicate *a) {
    m_count_fields.push_back(a->getCountField());
    DEBUG_ENTER("visitModelActivityReplicate");
    for (std::vector<vsc::IModelConstraintUP>::const_iterator
        it=a->constraints().begin();
        it!=a->constraints().end(); it++) {
        if (m_constraint_s.insert(it->get()).second) {
            DEBUG("Add constraint");
            m_constraints.push_back(it->get());
        }
    }
    DEBUG_LEAVE("visitModelActivityReplicate");
}

void TaskElaborateActivitySelectReplicateSizes::visitModelActivityScope(
    IModelActivityScope *a) {
    DEBUG_ENTER("visitModelActivityScope");
    for (std::vector<vsc::IModelConstraintUP>::const_iterator
        it=a->constraints().begin();
        it!=a->constraints().end(); it++) {
        if (m_constraint_s.insert(it->get()).second) {
            DEBUG("Add constraint");
            m_constraints.push_back(it->get());
        }
    }

    for (std::vector<IModelActivity *>::const_iterator
        it=a->activities().begin();
        it!=a->activities().end(); it++) {
        (*it)->accept(m_this);
    }
    DEBUG_LEAVE("visitModelActivityScope");
}

void TaskElaborateActivitySelectReplicateSizes::visitModelActivityTraverse(
    IModelActivityTraverse *a) {
    DEBUG_ENTER("visitModelActivityTraverse");

    for (std::vector<vsc::IModelConstraintUP>::const_iterator
        it=a->getTarget()->constraints().begin();
        it!=a->getTarget()->constraints().end(); it++) {
        if (m_constraint_s.insert(it->get()).second) {
            DEBUG("Add constraint:\n%s", vsc::PrettyPrinter().print(it->get()));
            m_constraints.push_back(it->get());
        }
    }

    if (a->getActivity()) {
        a->getActivity()->accept(m_this);
    }

    DEBUG_LEAVE("visitModelActivityTraverse");
}

vsc::IDebug *TaskElaborateActivitySelectReplicateSizes::m_dbg = 0;

}
