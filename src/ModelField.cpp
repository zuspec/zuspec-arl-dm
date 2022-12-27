/*
 * ModelField.cpp
 *
 *  Created on: Jun 18, 2022
 *      Author: mballance
 */

#include "ModelField.h"

namespace zsp {
namespace arl {
namespace dm {


ModelField::ModelField() {
	m_parent = 0;
	m_flags = vsc::dm::ModelFieldFlag::NoFlags;

}

ModelField::~ModelField() {
	// TODO Auto-generated destructor stub
}

void ModelField::addConstraint(vsc::dm::IModelConstraint *c) {
	m_constraints.push_back(vsc::dm::IModelConstraintUP(c));
}

void ModelField::addField(vsc::dm::IModelField *field) {
	m_fields.push_back(vsc::dm::IModelFieldUP(field));
}

vsc::dm::IModelField *ModelField::getField(int32_t idx) {
	return m_fields.at(idx).get();
}

}
}
}
