/**
 * TypeProcStmtAssign.h
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
#include "zsp/arl/dm/ITypeProcStmtAssign.h"

namespace zsp {
namespace arl {
namespace dm {




class TypeProcStmtAssign : public virtual ITypeProcStmtAssign {
public:
    TypeProcStmtAssign(
        vsc::dm::ITypeExpr      *lhs,
        TypeProcStmtAssignOp    op,
        vsc::dm::ITypeExpr      *rhs);

    virtual ~TypeProcStmtAssign();

    virtual vsc::dm::ITypeExpr *getLhs() override {
        return m_lhs.get();
    }

    virtual TypeProcStmtAssignOp op() const override {
        return m_op;
    }

    virtual vsc::dm::ITypeExpr *getRhs() override {
        return m_rhs.get();
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    vsc::dm::ITypeExprUP                m_lhs;
    TypeProcStmtAssignOp                m_op;
    vsc::dm::ITypeExprUP                m_rhs;

};

}
}
}


