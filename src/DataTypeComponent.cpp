/*
 * DataTypeComponent.cpp
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#include "DataTypeComponent.h"

namespace arl {

DataTypeComponent::DataTypeComponent(const std::string &name) : m_name(name) {
	// TODO Auto-generated constructor stub

}

DataTypeComponent::~DataTypeComponent() {
	// TODO Auto-generated destructor stub
}

void DataTypeComponent::addField(vsc::ITypeField *f) {
	m_fields.push_back(vsc::ITypeFieldUP(f));
}

void DataTypeComponent::addConstraint(vsc::ITypeConstraint *c) {
	m_constraints.push_back(vsc::ITypeConstraintUP(c));
}

vsc::IModelStructCreateHook *DataTypeComponent::getCreateHook() const {
	return m_create_hook.get();
}

void DataTypeComponent::setCreateHook(vsc::IModelStructCreateHook *hook) {
	m_create_hook = vsc::IModelStructCreateHookUP(hook);
}

const std::vector<IDataTypeAction *> &DataTypeComponent::getActionTypes() const {
	return m_action_types;
}

void DataTypeComponent::addActionType(IDataTypeAction *action_t) {
	m_action_types.push_back(action_t);
}

void DataTypeComponent::accept(vsc::IVisitor *v) {
	if (dynamic_cast<IVisitor *>(v)) {
		accept(dynamic_cast<IVisitor *>(v));
	} else {
		// TODO: abort?
	}
}

} /* namespace arl */
