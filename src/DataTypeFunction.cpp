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
#include "arl/IVisitor.h"
#include "DataTypeFunction.h"


namespace zsp {
namespace arl {
namespace dm {



DataTypeFunction::DataTypeFunction(
    IContext                    *ctxt,
    const std::string           &name,
    vsc::IDataType              *rtype,
    bool                        own_rtype) : 
        m_name(name), m_ret_type(rtype), m_ret_type_u(own_rtype?rtype:0),
        m_body(ctxt->mkTypeProcStmtScope()) {
}

DataTypeFunction::~DataTypeFunction() {

}

void DataTypeFunction::addParameter(IDataTypeFunctionParamDecl *p) {
    m_parameters.push_back(IDataTypeFunctionParamDeclUP(p));
}

void DataTypeFunction::accept(vsc::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitDataTypeFunction(this);
    }
}

}
}
}
