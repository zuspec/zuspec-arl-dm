/*
 * TestBuildModelComponent.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#include "TaskBuildModelComponent.h"

namespace arl {

TaskBuildModelComponent::TaskBuildModelComponent(IContext *ctxt) : m_ctxt(ctxt) {
	// TODO Auto-generated constructor stub

}

TaskBuildModelComponent::~TaskBuildModelComponent() {
	// TODO Auto-generated destructor stub
}

vsc::IModelField *TaskBuildModelComponent::build(
		arl::IDataTypeComponent *c,
		const std::string &name) {
	m_field_s.push_back(m_ctxt->mkModelFieldRoot(c, name));
	c->accept(this);
	return m_field_s.at(0);
}

void TaskBuildModelComponent::visitDataTypeComponent(IDataTypeComponent *t) {
//	m_ctxt->mkModelFieldRoot(type, name)
	VisitorBase::visitDataTypeComponent(t);
}

} /* namespace arl */
