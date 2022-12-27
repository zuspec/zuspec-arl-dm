/*
 * DataTypeActivityScope.cpp
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#include "DataTypeActivityScope.h"

namespace zsp {
namespace arl {
namespace dm {


DataTypeActivityScope::DataTypeActivityScope(const std::string &name) : m_name(name) {
	// TODO Auto-generated constructor stub

}

DataTypeActivityScope::~DataTypeActivityScope() {
	// TODO Auto-generated destructor stub
}

void DataTypeActivityScope::addField(vsc::dm::ITypeField *f) {
	f->setIndex(m_fields.size());
	m_fields.push_back(vsc::dm::ITypeFieldUP(f));
}

void DataTypeActivityScope::addConstraint(vsc::dm::ITypeConstraint *c) {
	m_constraints.push_back(vsc::dm::ITypeConstraintUP(c));
}

void DataTypeActivityScope::addActivity(ITypeFieldActivity *a) {
	// A non-data-field activity. Owned by the activities collection
	m_activities.push_back(a);
	m_activities_up.push_back(ITypeFieldActivityUP(a));
}

void DataTypeActivityScope::addActivityField(ITypeFieldActivity *a) {
	a->setIndex(m_fields.size());
	m_activities.push_back(a);
	m_fields.push_back(vsc::dm::ITypeFieldUP(a));
}


vsc::dm::IModelField *DataTypeActivityScope::mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) {

}

vsc::dm::IModelField *DataTypeActivityScope::mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type) {
			
}

}
}
}
