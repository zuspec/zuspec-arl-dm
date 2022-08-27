/*
 * ModelFieldRootComponent.cpp
 *
 *  Created on: May 17, 2022
 *      Author: mballance
 */

#include "arl/IVisitor.h"
#include "ModelFieldRootComponent.h"
#include "TaskBuildComponentMap.h"

namespace arl {

ModelFieldRootComponent::ModelFieldRootComponent(
		IContext			*ctxt,
		const std::string	&name,
		vsc::IDataType		*type) :
				m_ctxt(ctxt), m_name(name), m_type(type), m_parent(0) {
	m_flags = vsc::ModelFieldFlag::NoFlags;

}

ModelFieldRootComponent::~ModelFieldRootComponent() {
	// TODO Auto-generated destructor stub
}

void ModelFieldRootComponent::initCompTree() {
	m_comp_map = ComponentMapUP(TaskBuildComponentMap().build(this));
}

void ModelFieldRootComponent::addConstraint(vsc::IModelConstraint *c) {
	m_constraints.push_back(vsc::IModelConstraintUP(c));
}

void ModelFieldRootComponent::addField(vsc::IModelField *field) {
	field->setParent(this);
	m_fields.push_back(vsc::IModelFieldUP(field));
}

void ModelFieldRootComponent::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelFieldRootComponent(this);
	}
}

} /* namespace arl */
