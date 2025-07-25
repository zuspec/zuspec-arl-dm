/**
 * TypeProcStmtScope.h
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
#include "zsp/arl/dm/ITypeProcStmtScope.h"
#include "TypeProcStmt.h"

namespace zsp {
namespace arl {
namespace dm {




class TypeProcStmtScope : 
    public virtual ITypeProcStmtScope,
    public TypeProcStmt {
public:
    TypeProcStmtScope(
        IContext                            *ctxt
    );

    TypeProcStmtScope(
        IContext                            *ctxt,
        const std::vector<ITypeProcStmt *>  &stmts);

    virtual ~TypeProcStmtScope();

    virtual void addStatement(ITypeProcStmt *stmt, bool owned=true) override;

    virtual void insertStatement(
        int32_t                 i,
        ITypeProcStmt           *stmt) override;

    virtual int32_t addVariable(vsc::dm::ITypeVar *v, bool owned=true) override;

    virtual int32_t insertVariable(
        int32_t                 i,
        ITypeProcStmtVarDecl    *v) override;

    virtual int32_t getNumVariables() override {
        return m_variables.size();
    }

    virtual const std::vector<ITypeProcStmtUP> &getStatements() const override {
        return m_statements;
    }

    virtual const std::vector<vsc::dm::ITypeVarUP> &getVariables() const override {
        return m_variables;
    }

    virtual vsc::dm::IDataTypeStruct *getLocalsT() const override {
        return m_locals_t.get();
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    IContext                                    *m_ctxt;
    std::vector<ITypeProcStmtUP>                m_statements;
    std::vector<vsc::dm::ITypeVarUP>            m_variables;
    vsc::dm::IDataTypeStructUP                  m_locals_t;
};

}
}
}


