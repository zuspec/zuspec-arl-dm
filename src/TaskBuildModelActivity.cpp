/*
 * TaskBuildModelActivity.cpp
 *
 *  Created on: Jun 8, 2022
 *      Author: mballance
 */

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
	// TODO Auto-generated constructor stub

}

TaskBuildModelActivity::~TaskBuildModelActivity() {
	// TODO Auto-generated destructor stub
}

IModelActivity *TaskBuildModelActivity::build(ITypeFieldActivity *activity) {
	fprintf(stdout, "TaskBuildModelActivity::build\n");

	// We enter on a TypeField of the containing action

	// Push the field corresponding to this action scope
	// This will always be a scope, so it will always have a
	// data representation
	m_ctxt->pushField(m_ctxt->getField(-1)->getField(activity->getIndex()));

	fprintf(stdout, "  Activity scope is %s\n", m_ctxt->getField(-1)->name().c_str());

	activity->getDataType()->accept(m_this);

	m_ctxt->popField();


	return dynamic_cast<IModelActivity *>(
			m_ctxt->getField(-1)->getField(activity->getIndex()));
}

void TaskBuildModelActivity::visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) {
	fprintf(stdout, "visitDataTypeActivitySchedule\n");

	VisitorBase::visitDataTypeActivitySchedule(t);

}

void TaskBuildModelActivity::visitDataTypeActivitySequence(IDataTypeActivitySequence *t) {
	fprintf(stdout, "visitDataTypeActivitySequence\n");

	for (auto it=t->getActivities().begin(); it!=t->getActivities().end(); it++) {
		(*it)->accept(m_this);
	}

}

void TaskBuildModelActivity::visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) {
	fprintf(stdout, "visitDataTypeActivityTraverse\n");

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

	fprintf(stdout, "target: %s\n", target->name().c_str());
	ModelActivityTraverse *traverse = new ModelActivityTraverse(
			dynamic_cast<IModelFieldAction *>(target),
			with_c);

	IModelActivityScope *pscope = m_ctxt->getFieldT<IModelActivityScope>(-1);
	pscope->addActivity(traverse, true);

}

void TaskBuildModelActivity::visitTypeFieldActivity(ITypeFieldActivity *f) {
	fprintf(stdout, "visitTypeFieldActivity %s %d\n", f->name().c_str(), f->getIndex());

	if (f->getIndex() != -1) {
		// Link in the existing activity scope
		IModelActivityScope *pscope = m_ctxt->getFieldT<IModelActivityScope>(-1);
		fprintf(stdout, "Link into scope %p\n", pscope);
		vsc::IModelField *afield = m_ctxt->getField(-1)->getField(f->getIndex());
		// Link in, since the object is already owned by the 'fields' list
		pscope->addActivity(dynamic_cast<IModelActivity *>(afield), false);
		m_ctxt->pushField(afield);
	}

	f->getDataType()->accept(m_this);

	if (f->getIndex() != -1) {
		m_ctxt->popField();
	}
}

} /* namespace arl */
