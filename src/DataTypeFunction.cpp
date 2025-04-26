/*
 * DataTypeFunction.cpp
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
#include "zsp/arl/dm/IVisitor.h"
#include "DataTypeFunction.h"


namespace zsp {
namespace arl {
namespace dm {



DataTypeFunction::DataTypeFunction(
    IContext                    *ctxt,
    const std::string           &name,
    vsc::dm::IDataType          *rtype,
    bool                        own_rtype,
    DataTypeFunctionFlags       flags,
    IDataTypeArlStruct          *context) :
        m_ctxt(ctxt), m_name(name), m_ret_type(rtype), 
        m_ret_type_u(own_rtype?rtype:0), m_flags(flags), 
        m_context(context),
        m_body(ctxt->mkTypeProcStmtScope()) {
    m_parameters_t = vsc::dm::IDataTypeStructUP(
        ctxt->mkDataTypeStruct(name + "_params"));
}

DataTypeFunction::~DataTypeFunction() {

}

void DataTypeFunction::addParameter(IDataTypeFunctionParamDecl *p) {
    m_parameters.push_back(p);
    m_variables.push_back(vsc::dm::ITypeVarUP(p, false));
    m_parameters_t->addField(m_ctxt->mkTypeFieldPhy(
        p->name(),
        p->getDataType(),
        false,
        vsc::dm::TypeFieldAttr::NoAttr, 0));
}

void DataTypeFunction::addImportSpec(IDataTypeFunctionImport *spec) {
    m_import_specs.push_back(IDataTypeFunctionImportUP(spec));
}

void DataTypeFunction::accept(vsc::dm::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitDataTypeFunction(this);
    }
}

}
}
}
