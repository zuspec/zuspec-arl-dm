/*
 * TaskModelActionBuilder.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#include "TaskBuildModelAction.h"

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
	vsc::IModelField *ret = m_core.build(t, name);

	if (t->getCreateHook()) {
		t->getCreateHook()->create(ret);
	}

	return dynamic_cast<IModelFieldAction *>(ret);
}

void TaskBuildModelAction::visitDataTypeAction(IDataTypeAction *t) {
	if (m_ctxt->fieldStackSize() == 0) {
		m_ctxt->pushField(m_ctxt->ctxt()->mkModelFieldActionRoot(m_core.name(), t));
	}

//	m_ctxt->mkModelFieldRoot(type, name)
	VisitorDelegator::visitDataTypeAction(t);
}

} /* namespace arl */
