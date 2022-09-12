/*
 * DataTypeStruct.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "vsc/impl/TaskIsTypeFieldRef.h"
#include "DataTypeStruct.h"

namespace arl {

DataTypeStruct::DataTypeStruct(const std::string &name) : m_name(name) {
	// TODO Auto-generated constructor stub

}

DataTypeStruct::~DataTypeStruct() {
	// TODO Auto-generated destructor stub
}

void DataTypeStruct::addField(vsc::ITypeField *f) {
	f->setIndex(m_fields.size());
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

vsc::IModelStructCreateHook *DataTypeStruct::getCreateHook() const {
	return m_create_hook.get();
}

void DataTypeStruct::setCreateHook(vsc::IModelStructCreateHook *hook) {
	m_create_hook = vsc::IModelStructCreateHookUP(hook);
}

vsc::IModelField *DataTypeStruct::mkRootField(
		vsc::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) {
	vsc::IModelField *ret;

	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
		ret = ctxt->ctxt()->mkModelFieldRoot(this, name);

		// Need to build sub-fields and constraints
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

vsc::IModelField *DataTypeStruct::mkTypeField(
		vsc::IModelBuildContext		*ctxt,
		vsc::ITypeField				*type) {
	vsc::IModelField *ret;

	if (vsc::TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
		ret = ctxt->ctxt()->mkModelFieldType(type);
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

} /* namespace arl */
