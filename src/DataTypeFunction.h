/**
 * DataTypeFunction.h
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
#pragma once
#include "arl/IContext.h"
#include "arl/IDataTypeFunction.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypeFunction : public virtual IDataTypeFunction {
public:
    DataTypeFunction(
        IContext                *ctxt,
        const std::string       &name,
        vsc::IDataType          *rtype,
        bool                    own_rtype);

    virtual ~DataTypeFunction();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual vsc::IDataType *getReturnType() const override {
        return m_ret_type;
    }

    virtual const std::vector<IDataTypeFunctionParamDeclUP> &getParameters() const override {
        return m_parameters;
    }

    virtual void addParameter(IDataTypeFunctionParamDecl *p) override;

    virtual ITypeProcStmtScope *getBody() const override {
        return m_body.get();
    }

    virtual void accept(vsc::IVisitor *v) override;

private:
    std::string                                     m_name;
    vsc::IDataType                                  *m_ret_type;
    vsc::IDataTypeUP                                m_ret_type_u;
    std::vector<IDataTypeFunctionParamDeclUP>       m_parameters;
    ITypeProcStmtScopeUP                            m_body;


};

}
}
}


