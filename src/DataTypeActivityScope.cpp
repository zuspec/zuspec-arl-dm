/*
 * DataTypeActivityScope.cpp
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */
#include "vsc/dm/impl/ValRefInt.h"
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

int32_t DataTypeActivityScope::getByteSize() const {
    return m_field_sz + m_activity_sz;
}

int32_t DataTypeActivityScope::getActivityOffset() const {
    // TODO: deal with padding
    return m_field_sz;
}

void DataTypeActivityScope::addField(
    vsc::dm::ITypeField     *f,
    bool                    owned) {
	f->setIndex(m_fields.size());
    int32_t offset = m_field_sz;
    if (m_fields.size()) {
        int32_t new_sz = f->getByteSize();
        int32_t align = 1;
        if (new_sz <= vsc::dm::ValRefInt::native_sz()) {
            align = new_sz;
        }
        int32_t pad = (m_field_sz%align)?(align - (m_field_sz % align)):0;
        offset += pad;
        m_field_sz += pad;
    }
    m_field_sz += f->getByteSize();
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
    a->setIndex(m_activities.size());
    int32_t offset = m_activity_sz;
    if (m_fields.size()) {
        int32_t new_sz = a->getByteSize();
        int32_t align = 1;
        if (new_sz <= vsc::dm::ValRefInt::native_sz()) {
            align = new_sz;
        }
        int32_t pad = (m_activity_sz%align)?(align - (m_activity_sz % align)):0;
        offset += pad;
        m_activity_sz += pad;
    }
    m_activity_sz += a->getByteSize();
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
    return 0;
}

vsc::dm::IModelField *DataTypeActivityScope::mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type,
        const vsc::dm::ValRef           &val) {
    return 0;
}

}
}
}
