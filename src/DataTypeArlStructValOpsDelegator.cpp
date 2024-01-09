/*
 * DataTypeArlStructValOpsDelegator.cpp
 *
 * Copyright 2023 Matthew Ballance and Contributors
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
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/impl/ValRefInt.h"
#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "DataTypeArlStructValOpsDelegator.h"


namespace zsp {
namespace arl {
namespace dm {


DataTypeArlStructValOpsDelegator::DataTypeArlStructValOpsDelegator(
        IContext            *ctxt,
        const std::string   &name) : m_name(name), m_bytesz(0), m_num_builtin(0) {

}

DataTypeArlStructValOpsDelegator::~DataTypeArlStructValOpsDelegator() {

}

void DataTypeArlStructValOpsDelegator::addField(
    vsc::dm::ITypeField     *f,
    bool                    owned) {
	f->setIndex(m_fields.size());
    int32_t offset = m_bytesz;
    if (m_fields.size()) {
        int32_t new_sz = f->getByteSize();
        int32_t align = 1;
        if (new_sz <= vsc::dm::ValRefInt::native_sz()) {
            align = new_sz;
        }

        if (m_bytesz) {
            int32_t pad = (m_bytesz%align)?(align - (m_bytesz % align)):0;
            offset += pad;
            m_bytesz += pad;
        }
    }
    m_bytesz += f->getByteSize();
    f->setOffset(offset);
	m_fields.push_back(vsc::dm::ITypeFieldUP(f, owned));
}

const std::vector<vsc::dm::ITypeFieldUP> &DataTypeArlStructValOpsDelegator::getFields() const {
	return m_fields;
}

vsc::dm::ITypeField *DataTypeArlStructValOpsDelegator::getField(int32_t idx) {
    int32_t field_idx = m_num_builtin + idx;
    if (field_idx >= 0 && field_idx < m_fields.size()) {
        return m_fields.at(field_idx).get();
    } else {
        return 0;
    }
}

void DataTypeArlStructValOpsDelegator::addConstraint(
    vsc::dm::ITypeConstraint    *c,
    bool                        owned) {
	m_constraints.push_back(vsc::dm::ITypeConstraintUP(c, owned));
}

const std::vector<vsc::dm::ITypeConstraintUP> &DataTypeArlStructValOpsDelegator::getConstraints() const {
	return m_constraints;
}

vsc::dm::IModelStructCreateHook *DataTypeArlStructValOpsDelegator::getCreateHook() const {
	return m_create_hook.get();
}

void DataTypeArlStructValOpsDelegator::setCreateHook(
    vsc::dm::IModelStructCreateHook     *hook,
    bool                                owned) {
	m_create_hook = vsc::dm::IModelStructCreateHookUP(hook, owned);
}

const std::vector<ITypeExecUP> &DataTypeArlStructValOpsDelegator::getExecs(ExecKindT kind) const {
    std::map<ExecKindT, std::vector<ITypeExecUP>>::const_iterator it;

    if ((it=m_exec_m.find(kind)) != m_exec_m.end()) {
        return it->second;
    } else {
        return m_empty_exec_l;
    }
}

void DataTypeArlStructValOpsDelegator::addExec(ITypeExec *exec) {
    std::map<ExecKindT, std::vector<ITypeExecUP>>::iterator it;

    if ((it=m_exec_m.find(exec->getKind())) == m_exec_m.end()) {
        it = m_exec_m.insert({
            exec->getKind(), 
            std::vector<arl::dm::ITypeExecUP>()}).first;
    }
    it->second.push_back(ITypeExecUP(exec));
}

void DataTypeArlStructValOpsDelegator::addFunction(IDataTypeFunction *f, bool owned) {
    m_functions.push_back(IDataTypeFunctionUP(f, owned));
}

const std::vector<IDataTypeFunctionUP> &DataTypeArlStructValOpsDelegator::getFunctions() {
    return m_functions;
}

vsc::dm::IModelField *DataTypeArlStructValOpsDelegator::mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			    &name,
		bool						    is_ref) {
	vsc::dm::IModelField *ret;

	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
        vsc::dm::ValRefStruct val(ctxt->ctxt()->mkValRefStruct(this));
		ret = ctxt->ctxt()->mkModelFieldRoot(this, name, val);

		// Need to build sub-fields and constraints
		for (uint32_t i=0; i<getFields().size(); i++) {
            vsc::dm::ValRef val_s(val.getFieldRef(i));
			ret->addField(getField(i)->mkModelField(ctxt, val_s));
		}
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

vsc::dm::IModelField *DataTypeArlStructValOpsDelegator::mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type,
        const vsc::dm::ValRef           &val) {
	vsc::dm::IModelField *ret;

	if (vsc::dm::TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
        vsc::dm::ValRefStruct val_s(val);
        initVal(val_s);
		ret = ctxt->ctxt()->mkModelFieldType(type, val_s);

		for (uint32_t i=0; i<getFields().size(); i++) {
            int32_t idx = i - m_num_builtin;
            vsc::dm::ValRef val_f(val_s.getFieldRef(idx));
			ret->addField(getField(idx)->mkModelField(ctxt, val_f));
		}
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

std::vector<ITypeExecUP> DataTypeArlStructValOpsDelegator::m_empty_exec_l;

}
}
}
