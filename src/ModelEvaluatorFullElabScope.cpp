/*
 * ModelEvaluatorFullElabScope.cpp
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
#include "ModelEvaluatorFullElabScope.h"


namespace arl {


ModelEvaluatorFullElabScope::ModelEvaluatorFullElabScope(
    IContext            *ctxt,
    vsc::IRandState     *randstate,
    IModelActivityScope *scope) : 
        m_ctxt(ctxt), m_randstate(randstate), m_scope(scope),
        m_idx(-1) {
    DEBUG_INIT("ModelEvaluatorFullElabScope", ctxt->getDebugMgr());

    m_action = 0;
    m_iterator = 0;
}

ModelEvaluatorFullElabScope::~ModelEvaluatorFullElabScope() {

}

bool ModelEvaluatorFullElabScope::next() {
    DEBUG_ENTER("next idx=%d sz=%d", (m_idx+1), m_scope->activities().size());
    m_idx++;

    if (m_idx >= m_scope->activities().size()) {
        delete this;
        DEBUG_LEAVE("next - false");
        return false;
    }

    m_action = 0;
    m_iterator = 0;
    m_scope->activities().at(m_idx)->accept(m_this);

    DEBUG_LEAVE("next - %d", m_type);
    return true;
}

bool ModelEvaluatorFullElabScope::valid() {
    return (m_idx < m_scope->activities().size());
}

bool ModelEvaluatorFullElabScope::pop() {
    return false;
}

ModelEvalNodeT ModelEvaluatorFullElabScope::type() const {
    return m_type;
}

IModelFieldAction *ModelEvaluatorFullElabScope::action() {
    return m_action;
}

IModelEvalIterator *ModelEvaluatorFullElabScope::iterator() {
    return m_iterator;
}

void ModelEvaluatorFullElabScope::visitModelActivityScope(IModelActivityScope *a) {
    DEBUG_ENTER("visitModelActivityScope");
    // Return a
    ModelEvaluatorFullElabScope *scope = new ModelEvaluatorFullElabScope(
        m_ctxt,
        m_randstate->clone(), // Not sure about this
        a);
    m_iterator = scope;
    m_type = (a->getType() == ModelActivityScopeT::Parallel)?
        ModelEvalNodeT::Parallel:
        ModelEvalNodeT::Sequence;
    DEBUG_LEAVE("visitModelActivityScope");
}

void ModelEvaluatorFullElabScope::visitModelActivityTraverse(IModelActivityTraverse *a) {
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

    if (m_action->isCompound()) {
        m_iterator = new ModelEvaluatorFullElabScope(
            m_ctxt,
            m_randstate->next(),
            m_action->getActivity()
        );
    }

    DEBUG_LEAVE("visitModelActivityTraverse");
}

vsc::IDebug *ModelEvaluatorFullElabScope::m_dbg = 0;

}
