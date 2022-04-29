/*
 * TaskModelActionBuilder.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#include "TaskBuildModelAction.h"

namespace arl {

TaskBuildModelAction::TaskBuildModelAction(IContext *ctxt) :
		VisitorDelegator(&m_core), m_ctxt(ctxt), m_core(ctxt, this) {

}

TaskBuildModelAction::~TaskBuildModelAction() {
	// TODO Auto-generated destructor stub
}

vsc::IModelField *TaskBuildModelAction::build(
		IDataTypeAction 	*t,
		const std::string 	&name) {
	vsc::IModelField *ret = m_core.build(t, name);

	if (t->getCreateHook()) {
		t->getCreateHook()->create(ret);
	}

	return ret;
}

void TaskBuildModelAction::visitDataTypeAction(IDataTypeAction *t) {
	if (m_core.getFields().size() == 0) {
		m_core.pushField(m_ctxt->mkModelFieldRoot(t, m_core.name()));
	}

//	m_ctxt->mkModelFieldRoot(type, name)
	VisitorDelegator::visitDataTypeAction(t);
}

} /* namespace arl */
