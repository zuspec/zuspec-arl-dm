/*
 * ModelEvaluatorFullElabParallel.cpp
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
#include "ModelEvaluatorFullElabParallel.h"
#include "ModelEvaluatorFullElabSequence.h"


namespace arl {


ModelEvaluatorFullElabParallel::ModelEvaluatorFullElabParallel(
    IContext            *ctxt,
    vsc::IRandState     *randstate) : m_ctxt(ctxt), m_randstate(randstate) {
    DEBUG_INIT("ModelEvaluatorFullElabParallel", ctxt->getDebugMgr())
    m_idx = -1;
}

ModelEvaluatorFullElabParallel::~ModelEvaluatorFullElabParallel() {

}

void ModelEvaluatorFullElabParallel::addBranch(IModelActivity *branch) {
    m_branches.push_back(branch);
}

bool ModelEvaluatorFullElabParallel::next() {
    DEBUG_ENTER("next - idx=%d size=%d", (m_idx+1), m_branches.size());
    m_idx++;

    if (m_idx >= m_branches.size()) {
        delete this;
        DEBUG_LEAVE("next - false");
        return false;
    }

    m_type = ModelEvalNodeT::Action;
    m_action = 0;
    m_iterator = 0;
    m_branches.at(m_idx)->accept(m_this);

    DEBUG_LEAVE("next - %d", m_type);
    return true;
}

void ModelEvaluatorFullElabParallel::visitModelActivityParallel(
    IModelActivityParallel *a) {
    DEBUG_ENTER("visitModelActivityParallel");
    ModelEvaluatorFullElabParallel *par = new ModelEvaluatorFullElabParallel(
        m_ctxt, 
        m_randstate->next());

    m_type = ModelEvalNodeT::Parallel;
    m_iterator = par;
    DEBUG_LEAVE("visitModelActivityParallel");
}

void ModelEvaluatorFullElabParallel::visitModelActivitySequence(
    IModelActivitySequence *a) {
    DEBUG_ENTER("visitModelActivitySequence");
    ModelEvaluatorFullElabSequence *seq = new ModelEvaluatorFullElabSequence(
        m_ctxt,
        m_randstate->next(), // Not sure about this
        a);
    m_iterator = seq;
    m_type = ModelEvalNodeT::Sequence;
    DEBUG_LEAVE("visitModelActivitySequence");
}

void ModelEvaluatorFullElabParallel::visitModelActivityTraverse(
    IModelActivityTraverse *a) {
    DEBUG_ENTER("visitModelActivityTraverse");
    std::vector<vsc::IModelConstraint *> constraints;

    if (a->getWithC()) {
        constraints.push_back(a->getWithC());
    }

    // Add in the local action constraints
    for (std::vector<vsc::IModelConstraintUP>::const_iterator
        it=a->getTarget()->constraints().begin();
        it!=a->getTarget()->constraints().end(); it++) {
        constraints.push_back(it->get());
    }

    vsc::ICompoundSolverUP solver(m_ctxt->mkCompoundSolver());

    vsc::IRandStateUP state(m_randstate->next());
    bool result = solver->solve(
        state.get(),
        {a->getTarget()},
        constraints,
        vsc::SolveFlags::Randomize
            | vsc::SolveFlags::RandomizeDeclRand
            | vsc::SolveFlags::RandomizeTopFields);

    m_type = ModelEvalNodeT::Action;
    m_action = a->getTarget();
    DEBUG_LEAVE("visitModelActivityTraverse");
}

vsc::IDebug *ModelEvaluatorFullElabParallel::m_dbg = 0;

}
