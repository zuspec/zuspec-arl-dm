/**
 * TypeProcStmtIfElse.h
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
#include "zsp/arl/dm/ITypeProcStmtIfElse.h"

namespace zsp {
namespace arl {
namespace dm {




class TypeProcStmtIfElse : public virtual ITypeProcStmtIfElse {
public:
    TypeProcStmtIfElse(
        const std::vector<ITypeProcStmtIfClause *>  &if_clauses,
        ITypeProcStmt                               *else_clause);

    virtual ~TypeProcStmtIfElse();

    virtual const std::vector<ITypeProcStmtIfClauseUP> &getIfClauses() const override {
        return m_if_clauses;
    }

    virtual void addIfClause(ITypeProcStmtIfClause *if_c) override {
        m_if_clauses.push_back(ITypeProcStmtIfClauseUP(if_c));
    };

    virtual ITypeProcStmt *getElseClause() const override {
        return m_else_clause.get();
    }

    virtual void setElseClause(ITypeProcStmt *else_c) override {
        m_else_clause = ITypeProcStmtUP(else_c);
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    std::vector<ITypeProcStmtIfClauseUP>        m_if_clauses;
    ITypeProcStmtUP                             m_else_clause;
};

}
}
}


