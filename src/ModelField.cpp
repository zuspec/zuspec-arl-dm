/*
 * ModelField.cpp
 *
 *  Created on: Jun 18, 2022
 *      Author: mballance
 */

#include "ModelField.h"

namespace arl {

ModelField::ModelField() {
	m_parent = 0;
	m_flags = vsc::ModelFieldFlag::NoFlags;

}

ModelField::~ModelField() {
	// TODO Auto-generated destructor stub
}

void ModelField::addConstraint(vsc::IModelConstraint *c) {
	m_constraints.push_back(vsc::IModelConstraintUP(c));
}

void ModelField::addField(vsc::IModelField *field) {
	m_fields.push_back(vsc::IModelFieldUP(field));
}

vsc::IModelField *ModelField::getField(int32_t idx) {
	return m_fields.at(idx).get();
}

} /* namespace arl */
