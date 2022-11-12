/*
 * ModelEvaluatorIncrElab.cpp
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
#include "vsc/impl/DebugMacros.h"
#include "ModelActivityTraverse.h"
#include "ModelEvaluatorIncrElab.h"
#include "ModelEvalIteratorIncrElab.h"
#include "ModelEvalIteratorIncrElabMgr.h"
#include "ModelEvaluatorIncrElabSequence.h"


namespace arl {


ModelEvaluatorIncrElab::ModelEvaluatorIncrElab(IContext *ctxt) : m_ctxt(ctxt) {
    DEBUG_INIT("ModelEvaluatorIncrElab", ctxt->getDebugMgr());
	m_activity_idx = 0;
	m_next = 0;
	m_randstate = 0;
}

ModelEvaluatorIncrElab::~ModelEvaluatorIncrElab() {

}

IModelEvalIterator *ModelEvaluatorIncrElab::eval(
    const vsc::IRandState           *randstate,
    IModelFieldComponent            *root_comp,
    IDataTypeAction                 *root_action) {
	DEBUG_ENTER("eval");
	ModelBuildContext ctxt_b(m_ctxt);
	m_randstate = vsc::IRandStateUP(randstate->clone());

	// Create a sequence containing a traversal of the 
	// root action
	m_action = IModelFieldActionUP(
		root_action->mkRootFieldT<IModelFieldAction>(
			&ctxt_b,
			root_action->name(),
			false));
	ModelEvaluatorThread *root_thread = new ModelEvaluatorThread(
		m_ctxt, m_randstate->next());
	root_thread->pushComponent(root_comp);
	ModelEvaluatorIncrElabSequence *root_seq = new ModelEvaluatorIncrElabSequence(root_thread);
	root_seq->addActivity(new ModelActivityTraverse(
		m_action.get(), 
		0, 
		false,
		0, 
		false), true);
	root_thread->pushIterator(root_seq);

	
	// TODO: must determine the component context

	// Need to do initial setup work to create list of
	// top-level activities to solve

	DEBUG_LEAVE("eval");
	return root_thread;
}

IModelEvalIterator *ModelEvaluatorIncrElab::next() {
	DEBUG_ENTER("next idx=%d size=%d", m_activity_idx, m_activities.size());
	if (m_activity_idx >= m_activities.size()) {
		DEBUG_LEAVE("next -- no more activities");
		return 0;
	}

	m_next = 0;

	// Time to determine what to do next at the top level
	m_activities.at(m_activity_idx)->accept(this);
	m_activity_idx++;

	DEBUG_LEAVE("next - %p", m_next);
	return m_next;
}

void ModelEvaluatorIncrElab::visitModelActivityTraverse(IModelActivityTraverse *a) {
	DEBUG_ENTER("visitModelActivityTraverse");

	// Randomize action
	vsc::ICompoundSolverUP solver(m_ctxt->mkCompoundSolver());
	std::vector<vsc::IModelConstraint *> constraints;

	if (a->getWithC()) {
		constraints.push_back(a->getWithC());
	}

	solver->solve(
		m_randstate.get(),
		{a->getTarget()},
		constraints,
		vsc::SolveFlags::Randomize|vsc::SolveFlags::RandomizeDeclRand|vsc::SolveFlags::RandomizeTopFields
	);

	DEBUG("ModelActivityTraverse: target=%p", a->getTarget());

	m_next = new ModelEvalIteratorIncrElab({ModelEvalNodeT::Action, a->getTarget()});
	DEBUG_LEAVE("visitModelActivityTraverse");
}

vsc::IDebug *ModelEvaluatorIncrElab::m_dbg = 0;

}
