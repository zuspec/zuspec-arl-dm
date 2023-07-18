/*
 * DataTypePackedStruct.cpp
 *
 * Copyright 2022 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author:
 */
#include "vsc/dm/IContext.h"
#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "zsp/arl/dm/IVisitor.h"
#include "DataTypePackedStruct.h"


namespace zsp {
namespace arl {
namespace dm {


DataTypePackedStruct::DataTypePackedStruct(
    const std::string       &name,
    Endian                  endian) : 
        m_name(name), m_endian(endian), m_bytesz(-1) {

}

DataTypePackedStruct::~DataTypePackedStruct() {

}

void DataTypePackedStruct::addField(
    vsc::dm::ITypeField     *f,
    bool                    owned) {
	f->setIndex(m_fields.size());
	m_fields.push_back(vsc::dm::ITypeFieldUP(f, owned));
}

const std::vector<vsc::dm::ITypeFieldUP> &DataTypePackedStruct::getFields() const {
	return m_fields;
}

vsc::dm::ITypeField *DataTypePackedStruct::getField(int32_t idx) {
	return m_fields.at(idx).get();
}

void DataTypePackedStruct::addConstraint(
    vsc::dm::ITypeConstraint    *c,
    bool                        owned) {
	m_constraints.push_back(vsc::dm::ITypeConstraintUP(c, owned));
}

const std::vector<vsc::dm::ITypeConstraintUP> &DataTypePackedStruct::getConstraints() const {
	return m_constraints;
}

vsc::dm::IModelStructCreateHook *DataTypePackedStruct::getCreateHook() const {
	return m_create_hook.get();
}

void DataTypePackedStruct::setCreateHook(
    vsc::dm::IModelStructCreateHook     *hook,
    bool                                owned) {
	m_create_hook = vsc::dm::IModelStructCreateHookUP(hook, owned);
}

vsc::dm::IModelField *DataTypePackedStruct::mkRootField(
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

vsc::dm::IModelField *DataTypePackedStruct::mkTypeField(
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

void DataTypePackedStruct::accept(vsc::dm::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitDataTypePackedStruct(this);
    } else if (v->cascade()) {
        v->visitDataTypeStruct(this);
    }
}

}
}
}
