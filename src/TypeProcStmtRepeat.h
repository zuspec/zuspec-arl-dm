/**
 * TypeProcStmtRepeat.h
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
#include "zsp/arl/dm/ITypeProcStmtRepeat.h"
#include "vsc/dm/ITypeExpr.h"
#include "zsp/arl/dm/ITypeProcStmt.h"

namespace zsp {
namespace arl {
namespace dm {




class TypeProcStmtRepeat :
    public virtual ITypeProcStmtRepeat {
public:
    TypeProcStmtRepeat(
        vsc::dm::ITypeExpr      *cond,
        ITypeProcStmt           *body
    );

    virtual ~TypeProcStmtRepeat();

    virtual vsc::dm::ITypeExpr *getExpr() const override {
        return m_cond.get();
    }

    virtual ITypeProcStmt *getBody() const override {
        return m_body.get();
    }

    virtual int32_t addVariable(vsc::dm::ITypeVar *v, bool owned=true) override {
        int32_t id = m_variables.size();
        m_variables.push_back(vsc::dm::ITypeVarUP(v));
        return id;
    }

    virtual int32_t getNumVariables() override {
        return m_variables.size();
    }

    virtual const std::vector<vsc::dm::ITypeVarUP> &getVariables() const override {
        return m_variables;
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    vsc::dm::ITypeExprUP                    m_cond;
    ITypeProcStmtUP                         m_body;
    std::vector<vsc::dm::ITypeVarUP>        m_variables;


};

}
}
}


