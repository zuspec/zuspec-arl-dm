/*
 * TaskBuildModelActivity.cpp
 *
 *  Created on: Jun 8, 2022
 *      Author: mballance
 */

#include "DebugMacros.h"
#include "IsModelActivitySequence.h"
#include "TaskBuildModelActivity.h"
#include "TaskBuildModelConstraint.h"
#include "vsc/impl/TaskBuildModelExpr.h"
#include "vsc/impl/TaskResolveFieldRefExpr.h"
#include "ModelActivitySequence.h"
#include "ModelActivityTraverse.h"

namespace arl {

TaskBuildModelActivity::TaskBuildModelActivity(IModelBuildContext *ctxt) :
		m_ctxt(ctxt) {
	DEBUG_INIT("TaskBuildModelActivity");
}

TaskBuildModelActivity::~TaskBuildModelActivity() {
	// TODO Auto-generated destructor stub
}

IModelActivity *TaskBuildModelActivity::build(ITypeFieldActivity *activity) {
	DEBUG_ENTER("build");

	// We enter on a TypeField of the containing action

	// Push the field corresponding to this action scope
	// This will always be a scope, so it will always have a
	// data representation
	m_ctxt->pushBottomUpScope(
		m_ctxt->getTopDownScope()->getField(activity->getIndex()));

	DEBUG("  Activity scope is %s", m_ctxt->getBottomUpScope()->name().c_str());

	activity->getDataType()->accept(m_this);

	m_ctxt->popBottomUpScope();


	DEBUG_LEAVE("build");
	return dynamic_cast<IModelActivity *>(
			m_ctxt->getTopDownScope()->getField(activity->getIndex()));
}

void TaskBuildModelActivity::visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) {
	DEBUG_ENTER("visitDataTypeActivitySchedule");

	VisitorBase::visitDataTypeActivitySchedule(t);

	DEBUG_LEAVE("visitDataTypeActivitySchedule");
}

void TaskBuildModelActivity::visitDataTypeActivitySequence(IDataTypeActivitySequence *t) {
	DEBUG_ENTER("visitDataTypeActivitySequence");

	for (auto it=t->getActivities().begin(); it!=t->getActivities().end(); it++) {
		(*it)->accept(m_this);
	}

	DEBUG_LEAVE("visitDataTypeActivitySequence");
}

void TaskBuildModelActivity::visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) {
	DEBUG_ENTER("visitDataTypeActivityTraverse");

	// The traverse statement doesn't have a 'field' representation
	// Go ahead and create one now
	vsc::IModelConstraint *with_c = 0;
	vsc::IModelField *target = vsc::TaskResolveFieldRefExpr(m_ctxt).resolve(t->getTarget());

	// Note: two things can resolve from looking at the expression
	// - We recognize it as a constant expression that we can resolve to a single field
	// - We recognize that we'll need to perform further resolution at runtime
	//
	// Note: for now, we only handle the first case

	if (t->getWithC()) {
		with_c = TaskBuildModelConstraint(m_ctxt).build(t->getWithC());
	}

	DEBUG("target: %s", target->name().c_str());
	ModelActivityTraverse *traverse = new ModelActivityTraverse(
			dynamic_cast<IModelFieldAction *>(target),
			with_c);

	IModelActivityScope *pscope = m_ctxt->getBottomUpScopeT<IModelActivityScope>();
	pscope->addActivity(traverse, true);

	DEBUG_LEAVE("visitDataTypeActivityTraverse");
}

void TaskBuildModelActivity::visitTypeFieldActivity(ITypeFieldActivity *f) {
	DEBUG_ENTER("visitTypeFieldActivity %s %d", f->name().c_str(), f->getIndex());

	if (f->getIndex() != -1) {
		// Link in the existing activity scope
		IModelActivityScope *pscope = m_ctxt->getBottomUpScopeT<IModelActivityScope>();
		fprintf(stdout, "Link into scope %p\n", pscope);
#ifdef UNDEFINED
		vsc::IModelField *afield = m_ctxt->getField(-1)->getField(f->getIndex());
		// Link in, since the object is already owned by the 'fields' list
		pscope->addActivity(dynamic_cast<IModelActivity *>(afield), false);
		m_ctxt->pushField(afield);
#endif
	}

	f->getDataType()->accept(m_this);

#ifdef UNDEFINED
	if (f->getIndex() != -1) {
		m_ctxt->popField();
	}
#endif

	DEBUG_LEAVE("visitTypeFieldActivity %s %d", f->name().c_str(), f->getIndex());
}

} /* namespace arl */
