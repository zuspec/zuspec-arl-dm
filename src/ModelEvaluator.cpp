/*
 * ModelEvaluator.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#include "vsc/impl/ModelBuildContext.h"
#include "DebugMacros.h"
#include "ModelEvaluator.h"
#include "ModelEvalIterator.h"
#include "ModelEvalIteratorMgr.h"
#include "ModelEvaluatorSequence.h"
#include "ModelEvaluatorThread.h"
#include "ModelActivityTraverse.h"
#include "TaskBuildModelAction.h"
#include "TaskCollectTopLevelActivities.h"

namespace arl {

ModelEvaluator::ModelEvaluator(IContext *ctxt) : m_ctxt(ctxt) {
	m_activity_idx = 0;
	m_next = 0;
	m_randstate = 0;
	DEBUG_INIT("ModelEvaluator");
}

ModelEvaluator::~ModelEvaluator() {
	// TODO Auto-generated destructor stub
}

IModelEvalIterator *ModelEvaluator::eval(
			const vsc::IRandState		*randstate,
			IModelFieldComponent		*root_comp,
			IDataTypeAction				*root_action) {
	DEBUG_ENTER("eval");
	vsc::ModelBuildContext ctxt_b(m_ctxt);
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
	ModelEvaluatorSequence *root_seq = new ModelEvaluatorSequence(root_thread);
	root_seq->addActivity(new ModelActivityTraverse(m_action.get(), 0), true);
	root_thread->pushIterator(root_seq);

	
	// TODO: must determine the component context

	// Need to do initial setup work to create list of
	// top-level activities to solve

	DEBUG_LEAVE("eval");
	return root_thread;
}

IModelEvalIterator *ModelEvaluator::next() {
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

void ModelEvaluator::visitModelActivityTraverse(IModelActivityTraverse *a) {
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

	m_next = new ModelEvalIterator({ModelEvalNodeT::Action, a->getTarget()});
	DEBUG_LEAVE("visitModelActivityTraverse");
}

} /* namespace arl */
