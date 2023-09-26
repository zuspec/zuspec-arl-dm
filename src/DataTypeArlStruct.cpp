/*
 * DataTypeArlStruct.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "vsc/dm/IContext.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/IModelStructCreateHook.h"
#include "vsc/dm/ITypeField.h"
#include "vsc/dm/ITypeConstraint.h"
#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "DataTypeArlStruct.h"

namespace zsp {
namespace arl {
namespace dm {


DataTypeArlStruct::DataTypeArlStruct(const std::string &name) : 
    m_name(name), m_bytesz(-1) {
	// TODO Auto-generated constructor stub

}

DataTypeArlStruct::~DataTypeArlStruct() {
	// TODO Auto-generated destructor stub
}

void DataTypeArlStruct::addField(
    vsc::dm::ITypeField     *f,
    bool                    owned) {
	f->setIndex(m_fields.size());
	m_fields.push_back(vsc::dm::ITypeFieldUP(f, owned));
}

const std::vector<vsc::dm::ITypeFieldUP> &DataTypeArlStruct::getFields() const {
	return m_fields;
}

vsc::dm::ITypeField *DataTypeArlStruct::getField(int32_t idx) {
	return m_fields.at(idx).get();
}

void DataTypeArlStruct::addConstraint(
    vsc::dm::ITypeConstraint    *c,
    bool                        owned) {
	m_constraints.push_back(vsc::dm::ITypeConstraintUP(c, owned));
}

const std::vector<vsc::dm::ITypeConstraintUP> &DataTypeArlStruct::getConstraints() const {
	return m_constraints;
}

vsc::dm::IModelStructCreateHook *DataTypeArlStruct::getCreateHook() const {
	return m_create_hook.get();
}

void DataTypeArlStruct::setCreateHook(
    vsc::dm::IModelStructCreateHook     *hook,
    bool                                owned) {
	m_create_hook = vsc::dm::IModelStructCreateHookUP(hook, owned);
}

const std::vector<ITypeExecUP> &DataTypeArlStruct::getExecs(ExecKindT kind) const {
    std::map<ExecKindT, std::vector<ITypeExecUP>>::const_iterator it;

    if ((it=m_exec_m.find(kind)) != m_exec_m.end()) {
        return it->second;
    } else {
        return m_empty_exec_l;
    }
}

void DataTypeArlStruct::addExec(ITypeExec *exec) {
    std::map<ExecKindT, std::vector<ITypeExecUP>>::iterator it;

    if ((it=m_exec_m.find(exec->getKind())) == m_exec_m.end()) {
        it = m_exec_m.insert({
            exec->getKind(), 
            std::vector<arl::dm::ITypeExecUP>()}).first;
    }
    it->second.push_back(ITypeExecUP(exec));
}

void DataTypeArlStruct::addFunction(IDataTypeFunction *f, bool owned) {
    m_functions.push_back(IDataTypeFunctionUP(f, owned));
}

const std::vector<IDataTypeFunctionUP> &DataTypeArlStruct::getFunctions() {
    return m_functions;
}

vsc::dm::IModelField *DataTypeArlStruct::mkRootField(
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

vsc::dm::IModelField *DataTypeArlStruct::mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type,
        const vsc::dm::ValRef           &val) {
	vsc::dm::IModelField *ret;

	if (vsc::dm::TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
        vsc::dm::ValRefStruct val_s(val);
		ret = ctxt->ctxt()->mkModelFieldType(type, val_s);

		for (uint32_t i=0; i<getFields().size(); i++) {
            vsc::dm::ValRef val_f(val_s.getFieldRef(i));
			ret->addField(getField(i)->mkModelField(ctxt, val_f));
		}
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

std::vector<ITypeExecUP> DataTypeArlStruct::m_empty_exec_l;

}
}
}
