/*
 * DataTypeStruct.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "DataTypeStruct.h"

namespace zsp {
namespace arl {
namespace dm {


DataTypeStruct::DataTypeStruct(const std::string &name) : m_name(name) {
	// TODO Auto-generated constructor stub

}

DataTypeStruct::~DataTypeStruct() {
	// TODO Auto-generated destructor stub
}

void DataTypeStruct::addField(vsc::dm::ITypeField *f) {
	f->setIndex(m_fields.size());
	m_fields.push_back(vsc::dm::ITypeFieldUP(f));
}

const std::vector<vsc::dm::ITypeFieldUP> &DataTypeStruct::getFields() const {
	return m_fields;
}

vsc::dm::ITypeField *DataTypeStruct::getField(int32_t idx) {
	return m_fields.at(idx).get();
}

void DataTypeStruct::addConstraint(vsc::dm::ITypeConstraint *c) {
	m_constraints.push_back(vsc::dm::ITypeConstraintUP(c));
}

const std::vector<vsc::dm::ITypeConstraintUP> &DataTypeStruct::getConstraints() const {
	return m_constraints;
}

vsc::dm::IModelStructCreateHook *DataTypeStruct::getCreateHook() const {
	return m_create_hook.get();
}

void DataTypeStruct::setCreateHook(vsc::dm::IModelStructCreateHook *hook) {
	m_create_hook = vsc::dm::IModelStructCreateHookUP(hook);
}

vsc::dm::IModelField *DataTypeStruct::mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) {
	vsc::dm::IModelField *ret;

	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
		ret = ctxt->ctxt()->mkModelFieldRoot(this, name);

		// Need to build sub-fields and constraints
		for (std::vector<vsc::dm::ITypeFieldUP>::const_iterator
			it=getFields().begin();
			it!=getFields().end(); it++) {
			ret->addField((*it)->mkModelField(ctxt));
		}
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

vsc::dm::IModelField *DataTypeStruct::mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type) {
	vsc::dm::IModelField *ret;

	if (vsc::dm::TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
		ret = ctxt->ctxt()->mkModelFieldType(type);

		for (std::vector<vsc::dm::ITypeFieldUP>::const_iterator
			it=getFields().begin();
			it!=getFields().end(); it++) {
			ret->addField((*it)->mkModelField(ctxt));
		}
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

}
}
}
