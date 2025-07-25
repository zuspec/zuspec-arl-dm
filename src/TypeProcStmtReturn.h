/**
 * TypeProcStmtReturn.h
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
#include "zsp/arl/dm/ITypeProcStmtReturn.h"
#include "TypeProcStmt.h"

namespace zsp {
namespace arl {
namespace dm {




class TypeProcStmtReturn : 
    public virtual ITypeProcStmtReturn,
    public TypeProcStmt {
public:
    TypeProcStmtReturn(vsc::dm::ITypeExpr *expr);

    virtual ~TypeProcStmtReturn();

    virtual vsc::dm::ITypeExpr *getExpr() const override {
        return m_expr.get();
    }

    virtual void setExpr(vsc::dm::ITypeExpr *e, bool owned=true) override {
        m_expr = vsc::dm::ITypeExprUP(e, owned);
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    vsc::dm::ITypeExprUP            m_expr;
};

}
}
}


