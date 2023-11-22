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
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IDataTypeFunction.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypeFunction : public virtual IDataTypeFunction {
public:
    DataTypeFunction(
        IContext                *ctxt,
        const std::string       &name,
        vsc::dm::IDataType      *rtype,
        bool                    own_rtype,
        DataTypeFunctionFlags   flags);

    virtual ~DataTypeFunction();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual vsc::dm::IDataType *getReturnType() const override {
        return m_ret_type;
    }

    virtual const std::vector<IDataTypeFunctionParamDecl *> &getParameters() const override {
        return m_parameters;
    }

    virtual void addParameter(IDataTypeFunctionParamDecl *p) override;

    virtual vsc::dm::IDataTypeStruct *getParametersType() const override {
        return m_parameters_t.get();
    }

    virtual ITypeProcStmtScope *getParamScope() const override {
        return m_param_scope.get();
    }

    virtual vsc::dm::IDataTypeStruct *getContext() const override {
        return m_context;
    }

    virtual bool getIsExport() const override {
        return m_is_export;
    }

    virtual void setIsExport(bool e) override {
        m_is_export = e;
    }

    virtual ITypeProcStmtScope *getBody() const override {
        return m_body.get();
    }

    virtual const std::vector<IDataTypeFunctionImportUP> &getImportSpecs() const override {
        return m_import_specs;
    }

    virtual void addImportSpec(IDataTypeFunctionImport *spec) override;

    virtual DataTypeFunctionFlags getFlags() const override {
        return m_flags;
    }

    virtual bool hasFlags(DataTypeFunctionFlags f) const override {
        return (m_flags & f) != DataTypeFunctionFlags::NoFlags;
    }

    virtual void setAssociatedData(vsc::dm::IAssociatedData *data) override {
        m_associated_data = vsc::dm::IAssociatedDataUP(data);
    }

    virtual vsc::dm::IAssociatedData *getAssociatedData() const override {
        return m_associated_data.get();
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    IContext                                        *m_ctxt;
    std::string                                     m_name;
    vsc::dm::IDataType                              *m_ret_type;
    vsc::dm::IDataTypeUP                            m_ret_type_u;
    std::vector<IDataTypeFunctionParamDecl *>       m_parameters;
    vsc::dm::IDataTypeStructUP                      m_parameters_t;
    vsc::dm::IDataTypeStruct                        *m_context;
    bool                                            m_is_export;
    DataTypeFunctionFlags                           m_flags;
    ITypeProcStmtScopeUP                            m_param_scope;
    ITypeProcStmtScopeUP                            m_body;
    std::vector<IDataTypeFunctionImportUP>          m_import_specs;
    vsc::dm::IAssociatedDataUP                      m_associated_data;


};

}
}
}


