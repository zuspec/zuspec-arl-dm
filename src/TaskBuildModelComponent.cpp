/*
 * TestBuildModelComponent.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#include "TaskBuildModelComponent.h"

namespace arl {

TaskBuildModelComponent::TaskBuildModelComponent(IContext *ctxt) :
		VisitorDelegator(&m_core), m_ctxt(ctxt), m_core(ctxt, this) {
	// TODO Auto-generated constructor stub

}

TaskBuildModelComponent::~TaskBuildModelComponent() {
	// TODO Auto-generated destructor stub
}

vsc::IModelField *TaskBuildModelComponent::build(
		arl::IDataTypeComponent *c,
		const std::string &name) {
	return m_core.build(c, name);
}

void TaskBuildModelComponent::visitDataTypeComponent(IDataTypeComponent *t) {
	if (m_core.getFields().size() == 0) {
		m_core.pushField(m_ctxt->mkModelFieldRoot(t, m_core.name()));
	}

//	m_ctxt->mkModelFieldRoot(type, name)
	VisitorDelegator::visitDataTypeComponent(t);
}

void TaskBuildModelComponent::visitTypeFieldPool(ITypeFieldPool *f) {
	vsc::IModelFieldType *field = m_ctxt->mkModelFieldType(f);
	m_field_s.back()->addField(field);

	field->addField(0);
}

} /* namespace arl */
