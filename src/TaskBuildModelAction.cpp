/*
 * TaskModelActionBuilder.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#include "TaskBuildModelAction.h"
#include "TaskBuildModelActivity.h"
#include "ModelActivitySchedule.h"
#include "ModelActivitySequence.h"
#include "ModelActivityTraverse.h"

namespace arl {

TaskBuildModelAction::TaskBuildModelAction(IModelBuildContext *ctxt) :
		VisitorDelegator(&m_core), m_ctxt(ctxt), m_core(ctxt, this) {

}

TaskBuildModelAction::~TaskBuildModelAction() {
	// TODO Auto-generated destructor stub
}

IModelFieldAction *TaskBuildModelAction::build(
		IDataTypeAction 	*t,
		const std::string 	&name) {
	fprintf(stdout, "TaskBuildModelAction::build (%s)\n", t->name().c_str());
	IModelFieldAction *ret = dynamic_cast<IModelFieldAction *>(m_core.build(t, name));

	// Now, build out the activity
	fprintf(stdout, "post-build: %d entries ; ret=%s\n",
			m_ctxt->fieldStackSize(), ret->name().c_str());
	for (std::vector<vsc::IModelFieldUP>::const_iterator
			it=ret->fields().begin(); it!=ret->fields().end(); it++) {
		fprintf(stdout, "  Field: %s\n", (*it)->name().c_str());
	}
	m_ctxt->pushField(ret);
	for (auto it=t->activities().begin(); it!=t->activities().end(); it++) {
		IModelActivity *activity = TaskBuildModelActivity(m_ctxt).build(*it);
//		ret->addActivity(activity);
	}

	m_ctxt->popField();

	if (t->getCreateHook()) {
		t->getCreateHook()->create(ret);
	}

	return ret;
}

void TaskBuildModelAction::visitDataTypeAction(IDataTypeAction *t) {
	fprintf(stdout, "visitDataTypeAction\n");
	if (m_ctxt->fieldStackSize() == 0) {
		m_ctxt->pushField(m_ctxt->ctxt()->mkModelFieldActionRoot(m_core.name(), t));
	}

	fprintf(stdout, "Activities: %d\n", t->activities().size());

//	m_ctxt->mkModelFieldRoot(type, name)
	VisitorDelegator::visitDataTypeAction(t);
}

void TaskBuildModelAction::visitTypeFieldActivity(ITypeFieldActivity *f) {
	fprintf(stdout, "visitTypeFieldActivity %s\n", f->name().c_str());

	// Go visit the data-type
	m_activity_s.push_back(f);
	f->getDataType()->accept(this);
	m_activity_s.pop_back();

	// Only visit fields. Activities will be processed later
	IDataTypeActivityScope *scope = f->getDataTypeT<IDataTypeActivityScope>();

	for (std::vector<vsc::ITypeFieldUP>::const_iterator
			it=scope->getFields().begin();
			it!=scope->getFields().end(); it++) {
		(*it)->accept(this);
	}
}

void TaskBuildModelAction::visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) {
	fprintf(stdout, "visitDataTypeActivitySchedule\n");

	// Only build out the

}

void TaskBuildModelAction::visitDataTypeActivitySequence(IDataTypeActivitySequence *t) {
	fprintf(stdout, "visitDataTypeActivitySequence\n");
	ModelActivitySequence *seq =
			new ModelActivitySequence(m_activity_s.back()->name(), t);

	if (m_ctxt->getFieldT<IModelFieldAction>(-1)) {
		m_ctxt->getFieldT<IModelFieldAction>(-1)->addActivity(seq);
	} else {
		m_ctxt->getFieldT<IModelActivityScope>(-1)->addActivity(seq);
	}

	// Only build out fields for now
	m_ctxt->pushField(seq);
	for (std::vector<vsc::ITypeFieldUP>::const_iterator
			it=t->getFields().begin();
			it!=t->getFields().end(); it++) {
		(*it)->accept(this);
	}
	m_ctxt->popField();
}

void TaskBuildModelAction::visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) {
	fprintf(stdout, "visitDataTypeActivityTraverse\n");
//	m_ctxt->getField(-1)->addField(new ModelActivityTraverse(0, 0));

}

} /* namespace arl */
