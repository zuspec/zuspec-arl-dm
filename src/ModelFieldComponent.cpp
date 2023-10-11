/*
 * ModelFieldComponent.cpp
 *
 *  Created on: May 17, 2022
 *      Author: mballance
 */

#include "zsp/arl/dm/IVisitor.h"
#include "ModelFieldComponent.h"
#include "ModelFieldComponentRoot.h"
#include "TaskBuildComponentMap.h"
#include "TaskPopulateResourcePools.h"

namespace zsp {
namespace arl {
namespace dm {


ModelFieldComponent::ModelFieldComponent(
	const std::string		&name,
	IDataTypeComponent		*type,
    const vsc::dm::ValRef   &val) : m_name(name), m_dt(type), m_type(0) {
	m_id = -1;
    m_val = val;
}

ModelFieldComponent::ModelFieldComponent(
	vsc::dm::ITypeField			*type) : 
		m_name(type->name()), m_dt(type->getDataType()), m_type(type) {

}

ModelFieldComponent::~ModelFieldComponent() {
	// TODO Auto-generated destructor stub
}


void ModelFieldComponent::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<arl::dm::IVisitor *>(v)) {
		dynamic_cast<arl::dm::IVisitor *>(v)->visitModelFieldComponent(this);
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

}
}
}
