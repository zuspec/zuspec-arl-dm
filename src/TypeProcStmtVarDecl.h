/**
 * TypeProcStmtVarDecl.h
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
#include "zsp/arl/dm/ITypeProcStmtVarDecl.h"

namespace zsp {
namespace arl {
namespace dm {



class TypeProcStmtVarDecl : public virtual ITypeProcStmtVarDecl {
public:
    TypeProcStmtVarDecl(
        const std::string           &name,
        vsc::dm::IDataType              *type,
        bool                        own,
        vsc::dm::ITypeExpr              *init);

    virtual ~TypeProcStmtVarDecl();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual vsc::dm::IDataType *getDataType() const override {
        return m_type;
    }

    virtual vsc::dm::ITypeExpr *getInit() const override {
        return m_init.get();
    }

    virtual vsc::dm::IAssociatedData *getAssociatedData() const override {
        return m_assoc_data.get();
    }
    
    virtual void setAssociatedData(vsc::dm::IAssociatedData *d, bool owned=true) override {
        m_assoc_data = vsc::dm::IAssociatedDataUP(d, owned);
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    std::string                     m_name;
    vsc::dm::IDataType              *m_type;
    vsc::dm::IDataTypeUP            m_type_u;
    vsc::dm::ITypeExprUP            m_init;
    vsc::dm::IAssociatedDataUP      m_assoc_data;
};

}
}
}


