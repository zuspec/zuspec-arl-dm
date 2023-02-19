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

void DataTypeActivityScope::addField(
    vsc::dm::ITypeField     *f,
    bool                    owned) {
	f->setIndex(m_fields.size());
	m_fields.push_back(vsc::dm::ITypeFieldUP(f, owned));
}

void DataTypeActivityScope::addConstraint(
    vsc::dm::ITypeConstraint    *c,
    bool                        owned) {
	m_constraints.push_back(vsc::dm::ITypeConstraintUP(c, owned));
}

void DataTypeActivityScope::addActivity(
    ITypeFieldActivity      *a,
    bool                    owned) {
	// A non-data-field activity. Owned by the activities collection
	m_activities.push_back(ITypeFieldActivityUP(a, owned));
}

void DataTypeActivityScope::addActivityField(ITypeFieldActivity *a) {
	a->setIndex(m_fields.size());
	m_activities.push_back(ITypeFieldActivityUP(a, false));
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
