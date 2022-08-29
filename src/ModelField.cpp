/*
 * ModelField.cpp
 *
 *  Created on: Jun 18, 2022
 *      Author: mballance
 */

#include "ModelField.h"

namespace arl {

ModelField::ModelField(
	const std::string 	&name,
	vsc::IDataType		*type) : m_name(name), m_type(type) {
	m_parent = 0;
	m_flags = vsc::ModelFieldFlag::NoFlags;
}

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
	fprintf(stdout, "ModelField::addField %d %p %s\n", 
		m_fields.size(), field, field->name().c_str());
	m_fields.push_back(vsc::IModelFieldUP(field));
}

vsc::IModelField *ModelField::getField(int32_t idx) {
	fprintf(stdout, "ModelField::getField: %d %p %s\n", 
		idx, m_fields.at(idx).get(), m_fields.at(idx).get()->name().c_str());
	return m_fields.at(idx).get();
}

} /* namespace arl */
