/*
 * ModelFieldComponent.cpp
 *
 *  Created on: May 17, 2022
 *      Author: mballance
 */

#include "arl/IVisitor.h"
#include "ModelFieldComponent.h"
#include "ModelFieldComponentRoot.h"
#include "TaskBuildComponentMap.h"
#include "TaskPopulateResourcePools.h"

namespace arl {

ModelFieldComponent::ModelFieldComponent(
	const std::string		&name,
	IDataTypeComponent		*type) : m_name(name), m_dt(type), m_type(0) {
	m_id = -1;
}

ModelFieldComponent::ModelFieldComponent(
	vsc::ITypeField			*type) : 
		m_name(type->name()), m_dt(type->getDataType()), m_type(type) {

}

ModelFieldComponent::~ModelFieldComponent() {
	// TODO Auto-generated destructor stub
}


void ModelFieldComponent::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelFieldComponent(this);
	} else if (v->cascade()) {
		v->visitModelField(this);
	}
}

ModelFieldComponentRoot *ModelFieldComponent::getRoot() {
	ModelFieldComponent *ret = this;

	while (ret->getParent()) {
		ret = ret->getParentT<ModelFieldComponent>();
	}

	return dynamic_cast<ModelFieldComponentRoot *>(ret);
}

} /* namespace arl */
