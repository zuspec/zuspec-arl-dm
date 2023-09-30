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
#include "zsp/arl/dm/ITypeProcStmtScope.h"

namespace zsp {
namespace arl {
namespace dm {




class TypeProcStmtScope : public virtual ITypeProcStmtScope {
public:
    TypeProcStmtScope();

    TypeProcStmtScope(const std::vector<ITypeProcStmt *> &stmts);

    virtual ~TypeProcStmtScope();

    virtual void addStatement(ITypeProcStmt *stmt) override;

    virtual int32_t addVariable(ITypeProcStmtVarDecl *v) override;

    virtual int32_t getNumVariables() override {
        return m_variables.size();
    }

    virtual const std::vector<ITypeProcStmtUP> &getStatements() const override {
        return m_statements;
    }

    virtual const std::vector<ITypeProcStmtVarDeclUP> &getVariables() const override {
        return m_variables;
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    std::vector<ITypeProcStmtUP>                m_statements;
    std::vector<ITypeProcStmtVarDeclUP>         m_variables;
};

}
}
}


