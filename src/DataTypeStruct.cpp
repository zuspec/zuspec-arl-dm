/*
 * DataTypeStruct.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "DataTypeStruct.h"

namespace arl {

DataTypeStruct::DataTypeStruct(const std::string &name) : m_name(name) {
	// TODO Auto-generated constructor stub

}

DataTypeStruct::~DataTypeStruct() {
	// TODO Auto-generated destructor stub
}

void DataTypeStruct::addField(vsc::ITypeField *f) {
	m_fields.push_back(vsc::ITypeFieldUP(f));
}

const std::vector<vsc::ITypeFieldUP> &DataTypeStruct::getFields() const {
	return m_fields;
}

vsc::ITypeField *DataTypeStruct::getField(int32_t idx) {
	return m_fields.at(idx).get();
}

void DataTypeStruct::addConstraint(vsc::ITypeConstraint *c) {
	m_constraints.push_back(vsc::ITypeConstraintUP(c));
}

const std::vector<vsc::ITypeConstraintUP> &DataTypeStruct::getConstraints() const {
	return m_constraints;
}

} /* namespace arl */
