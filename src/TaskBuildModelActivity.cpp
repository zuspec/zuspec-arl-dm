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


	// The root activity field requires special handling, so
	// visit the type directly. The parent of the root activity
	// is the action, and we cannot add it as a child
	fprintf(stdout, "Parent scope=%s\n", m_ctxt->getField(-1)->name().c_str());
	fprintf(stdout, "  push index %d ; name %s\n",
			activity->getIndex(), m_ctxt->getField(-1)->name().c_str());
	m_ctxt->pushField(m_ctxt->getField(-1)->getField(activity->getIndex()));

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
	vsc::IModelExpr *fieldref = vsc::TaskBuildModelExpr(m_ctxt).build(t->getTarget());
	vsc::IModelConstraint *with_c = 0;

	if (t->getWithC()) {
		with_c = TaskBuildModelConstraint(m_ctxt).build(t->getWithC());
	}

	/*
	ModelActivityTraverse *traverse = new ModelActivityTraverse(
			target,
			with_c);
	 */

}

void TaskBuildModelActivity::visitTypeFieldActivity(ITypeFieldActivity *f) {
	fprintf(stdout, "visitTypeFieldActivity\n");
	// Obtain the corresponding scope that we need to refer to
	IModelActivityScope *parent = m_ctxt->getFieldT<IModelActivityScope>(-1);
	IModelActivity *child = parent->getFieldT<IModelActivity>(f->getIndex());
	parent->addActivity(child);
	m_ctxt->pushField(parent);

	f->getDataType()->accept(m_this);

	m_ctxt->popField();
}

} /* namespace arl */
