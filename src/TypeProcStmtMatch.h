/**
 * TypeProcStmtMatch.h
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
#include "zsp/arl/dm/ITypeProcStmtMatch.h"
#include "TypeProcStmt.h"

namespace zsp {
namespace arl {
namespace dm {



class TypeProcStmtMatch : 
    public virtual ITypeProcStmtMatch,
    public TypeProcStmt {
public:
    TypeProcStmtMatch(
        vsc::dm::ITypeExpr          *cond
    );

    virtual ~TypeProcStmtMatch();

    virtual vsc::dm::ITypeExpr *getCond() const override {
        return m_cond.get();
    }

    virtual ITypeProcStmt *getDefault() const override {
        return m_default.get();
    }

    virtual void setDefault(ITypeProcStmt *s) override {
        m_default = ITypeProcStmtUP(s);
    }

    virtual void addChoice(ITypeProcStmtMatchChoice *choice) override {
        m_choices.push_back(ITypeProcStmtMatchChoiceUP(choice));
    }

    virtual const std::vector<ITypeProcStmtMatchChoiceUP> &getChoices() const override {
        return m_choices;
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    vsc::dm::ITypeExprUP                                m_cond;
    ITypeProcStmtUP                                 m_default;
    std::vector<ITypeProcStmtMatchChoiceUP>         m_choices;
};

}
}
}


