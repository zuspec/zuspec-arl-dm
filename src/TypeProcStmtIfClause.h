/**
 * TypeProcStmtIfClause.h
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
#pragma once
#include "zsp/arl/dm/ITypeProcStmtIfClause.h"

namespace zsp {
namespace arl {
namespace dm {


class TypeProcStmtIfClause : public virtual ITypeProcStmtIfClause {
public:
    TypeProcStmtIfClause(
        vsc::dm::ITypeExpr          *cond,
        ITypeProcStmt               *stmt);

    virtual ~TypeProcStmtIfClause();

    virtual vsc::dm::ITypeExpr *getCond() const override {
        return m_cond.get();
    }

    virtual ITypeProcStmt *getStmt() const override {
        return m_stmt.get();
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    vsc::dm::ITypeExprUP            m_cond;
    ITypeProcStmtUP                 m_stmt;


};

}
}
}


