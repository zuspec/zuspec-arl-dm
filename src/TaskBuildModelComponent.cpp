/*
 * TestBuildModelComponent.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#include "TaskBuildModelComponent.h"
#include "ModelFieldRootComponent.h"

namespace arl {

TaskBuildModelComponent::TaskBuildModelComponent(IContext *ctxt) :
		VisitorDelegator(&m_core), m_ctxt(ctxt), m_core(ctxt, this) {
	// TODO Auto-generated constructor stub

}

TaskBuildModelComponent::~TaskBuildModelComponent() {
	// TODO Auto-generated destructor stub
}

IModelFieldRootComponent *TaskBuildModelComponent::build(
		arl::IDataTypeComponent *c,
		const std::string &name) {
	ModelFieldRootComponent *root_comp = dynamic_cast<ModelFieldRootComponent *>(m_core.build(c, name));

	root_comp->initCompTree();

	return root_comp;
}

void TaskBuildModelComponent::visitDataTypeComponent(IDataTypeComponent *t) {
	if (m_core.getFields().size() == 0) {
		m_core.pushField(new ModelFieldRootComponent(
				m_ctxt,
				m_core.name(),
				t));
	}

//	m_ctxt->mkModelFieldRoot(type, name)
	VisitorDelegator::visitDataTypeComponent(t);
}

void TaskBuildModelComponent::visitTypeFieldPool(ITypeFieldPool *f) {
	vsc::IModelFieldType *field = m_ctxt->mkModelFieldType(f);
	m_core.getFields().back()->addField(field);

	// A Pool-type field is not an instance of the contained type,
	// though that is the stated type.
	// A pool-type field does require a 'size' field in order to
	// track the specified size

	vsc::IDataTypeInt *vsc_int32_t = m_ctxt->findDataTypeInt(true, 32);
	if (!vsc_int32_t) {
		vsc_int32_t = m_ctxt->mkDataTypeInt(true, 32);
		m_ctxt->addDataTypeInt(vsc_int32_t);
	}

	vsc::IModelField *size = m_ctxt->mkModelFieldRoot(vsc_int32_t, "size");
	size->val()->set_val_i(f->getDeclSize());
	field->addField(size);
}

} /* namespace arl */
