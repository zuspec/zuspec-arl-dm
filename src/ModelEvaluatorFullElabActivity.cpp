/*
 * ModelEvaluatorFullElabActivity.cpp
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
#include "ModelEvaluatorFullElabActivity.h"
#include "ModelEvaluatorFullElabParallel.h"
#include "ModelEvaluatorFullElabSequence.h"


namespace arl {


ModelEvaluatorFullElabActivity::ModelEvaluatorFullElabActivity(
    IContext                *ctxt,
    vsc::IRandState         *randstate,
    IModelActivity          *activity) : m_ctxt(ctxt), m_randstate(randstate) {
    DEBUG_INIT("ModelEvaluatorFullElabActivity", m_ctxt->getDebugMgr());
    m_activity = activity;
    m_taken = false;

}

ModelEvaluatorFullElabActivity::~ModelEvaluatorFullElabActivity() {

}

bool ModelEvaluatorFullElabActivity::next() {
    DEBUG_ENTER("next");

    if (m_taken) {
        DEBUG_LEAVE("next - done");
        delete this;
        return false;
    }

    m_type = ModelEvalNodeT::Action;
    m_action = 0;
    m_iterator = 0;

    m_activity->accept(m_this);

    m_taken = true;

    DEBUG_LEAVE("next");
    return true;
}

void ModelEvaluatorFullElabActivity::visitModelActivityParallel(IModelActivityParallel *a) {
    DEBUG_ENTER("visitModelActivityParallel");
    ModelEvaluatorFullElabParallel *par = new ModelEvaluatorFullElabParallel(
        m_ctxt, 
        m_randstate->next());

    for (std::vector<IModelActivity *>::const_iterator
        it=a->branches().begin();
        it!=a->branches().end(); it++) {
        par->addBranch(*it);
    }

    m_type = ModelEvalNodeT::Parallel;
    m_iterator = par;

    DEBUG_LEAVE("visitModelActivityParallel");
}


void ModelEvaluatorFullElabActivity::visitModelActivitySequence(IModelActivitySequence *a) {
    DEBUG_ENTER("visitModelActivitySequence");

    // Return a
    ModelEvaluatorFullElabSequence *seq = new ModelEvaluatorFullElabSequence(
        m_ctxt,
        m_randstate->clone(), // Not sure about this
        a);
    m_iterator = seq;
    m_type = ModelEvalNodeT::Sequence;

    DEBUG_LEAVE("visitModelActivitySequence");
}

void ModelEvaluatorFullElabActivity::visitModelActivityTraverse(IModelActivityTraverse *a) {
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

    bool result = solver->solve(
        m_randstate.get(),
        {a->getTarget()},
        constraints,
        vsc::SolveFlags::Randomize
            | vsc::SolveFlags::RandomizeDeclRand
            | vsc::SolveFlags::RandomizeTopFields);

    m_type = ModelEvalNodeT::Action;
    m_action = a->getTarget();

    DEBUG_LEAVE("visitModelActivityTraverse");
}

vsc::IDebug *ModelEvaluatorFullElabActivity::m_dbg = 0;

}

