/*
 * TestBuildModelComponent.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#include "TaskBuildModelComponent.h"
#include "ModelFieldComponentRoot.h"

namespace arl {

TaskBuildModelComponent::TaskBuildModelComponent(IModelBuildContext *ctxt) :
		VisitorDelegator(&m_core), m_ctxt(ctxt), m_core(ctxt, this) {
	// TODO Auto-generated constructor stub

}

TaskBuildModelComponent::~TaskBuildModelComponent() {
	// TODO Auto-generated destructor stub
}

IModelFieldComponent *TaskBuildModelComponent::build(
		arl::IDataTypeComponent *c,
		const std::string &name) {
	ModelFieldComponent *root_comp = dynamic_cast<ModelFieldComponent *>(m_core.build(c, name));

	root_comp->initCompTree();

	return root_comp;
}

void TaskBuildModelComponent::visitDataTypeComponent(IDataTypeComponent *t) {
#ifdef UNDEFINED
	if (m_ctxt->fieldStackSize() == 0) {
		m_ctxt->pushField(new ModelFieldComponentRoot(
				m_ctxt->ctxt(),
				m_core.name(),
				t));
	}
#endif

//	m_ctxt->mkModelFieldRoot(type, name)
	VisitorDelegator::visitDataTypeComponent(t);
}

void TaskBuildModelComponent::visitTypeFieldPool(ITypeFieldPool *f) {
	vsc::IModelFieldType *field = m_ctxt->ctxt()->mkModelFieldType(f);
	m_ctxt->getTopDownScope()->addField(field);

	// A Pool-type field is not an instance of the contained type,
	// though that is the stated type.
	// A pool-type field does require a 'size' field in order to
	// track the specified size

	vsc::IDataTypeInt *vsc_int32_t = m_ctxt->ctxt()->findDataTypeInt(true, 32);
	if (!vsc_int32_t) {
		vsc_int32_t = m_ctxt->ctxt()->mkDataTypeInt(true, 32);
		m_ctxt->ctxt()->addDataTypeInt(vsc_int32_t);
	}

	vsc::IModelField *size = m_ctxt->ctxt()->mkModelFieldRoot(vsc_int32_t, "size");
	size->val()->set_val_i(f->getDeclSize());
	field->addField(size);
}

} /* namespace arl */
