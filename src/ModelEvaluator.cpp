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
#include "ModelActivityTraverse.h"
#include "TaskBuildModelAction.h"
#include "TaskCollectTopLevelActivities.h"

namespace arl {

ModelEvaluator::ModelEvaluator(IContext *ctxt) : m_ctxt(ctxt) {
	m_activity_idx = 0;
	m_next = 0;
	DEBUG_INIT("ModelEvaluator");
}

ModelEvaluator::~ModelEvaluator() {
	// TODO Auto-generated destructor stub
}

IModelEvalIterator *ModelEvaluator::eval(
			vsc::IModelField	*root_comp,
			IDataTypeAction		*root_action) {
	DEBUG_ENTER("eval");
	vsc::ModelBuildContext ctxt_b(m_ctxt);
	m_action = IModelFieldActionUP(
		root_action->getFactory()->createRootFieldT<IModelFieldAction>(
			&ctxt_b,
			root_action,
			root_action->name(),
			false));
	
	if (m_action->activities().size() == 1) {
		// Have activities in a sequence
		TaskCollectTopLevelActivities().collect(
			m_activities,
			m_action->activities().at(0));
	} else if (m_action->activities().size() > 1) {
		// Need a schedule before running
		DEBUG("TODO: need to schedule actions");
	} else {
		// Just have the action
		m_dummy_activity = IModelActivityTraverseUP(
			new ModelActivityTraverse(m_action.get(), 0));
		m_activities.push_back(m_dummy_activity.get());
	}

	// Need to do initial setup work to create list of
	// top-level activities to solve

	DEBUG_LEAVE("eval");
	return new ModelEvalIteratorMgr(this);
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
	// TODO: randomize action

	DEBUG("ModelActivityTraverse: target=%p", a->getTarget());

	m_next = new ModelEvalIterator({ModelEvalNodeT::Action, a->getTarget()});
	DEBUG_LEAVE("visitModelActivityTraverse");
}

} /* namespace arl */
