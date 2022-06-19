/*
 * DataTypeActivityScope.cpp
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#include "DataTypeActivityScope.h"

namespace arl {

DataTypeActivityScope::DataTypeActivityScope(const std::string &name) :
		m_name(name) {
	// TODO Auto-generated constructor stub

}

DataTypeActivityScope::~DataTypeActivityScope() {
	// TODO Auto-generated destructor stub
}

void DataTypeActivityScope::addField(vsc::ITypeField *f) {
	f->setIndex(m_fields.size());
	f->setParent(this);
	m_fields.push_back(vsc::ITypeFieldUP(f));
}

void DataTypeActivityScope::addConstraint(vsc::ITypeConstraint *c) {
	m_constraints.push_back(vsc::ITypeConstraintUP(c));
}

void DataTypeActivityScope::addActivity(ITypeFieldActivity *a) {
	m_activities.push_back(ITypeFieldActivityUP(a));
}

} /* namespace arl */
