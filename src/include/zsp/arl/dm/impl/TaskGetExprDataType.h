/**
 * TaskGetExprDataType.h
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
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/impl/VisitorBase.h" 

namespace zsp {
namespace arl {
namespace dm {



class TaskGetExprDataType :
    public virtual arl::dm::VisitorBase {
public:

    TaskGetExprDataType(IContext *ctxt) : m_ctxt(ctxt) { }

    virtual ~TaskGetExprDataType() { }

    vsc::dm::IDataType *get_type(vsc::dm::ITypeExpr *e) {
        m_type = 0;
        e->accept(m_this);
        return m_type;
    }

    virtual void visitTypeExprBin(vsc::dm::ITypeExprBin *e) {
        switch (e->op()) {
	        case vsc::dm::BinOp::Eq:
	        case vsc::dm::BinOp::Ne:
	        case vsc::dm::BinOp::Gt:
	        case vsc::dm::BinOp::Ge:
	        case vsc::dm::BinOp::Lt:
	        case vsc::dm::BinOp::Le:
                m_type = m_ctxt->getDataTypeCore(vsc::dm::DataTypeCoreE::Bool);
                break;
	        case vsc::dm::BinOp::Add:
	        case vsc::dm::BinOp::Sub:
	        case vsc::dm::BinOp::Div:
	        case vsc::dm::BinOp::Mul:
	        case vsc::dm::BinOp::Mod:
	        case vsc::dm::BinOp::BinAnd:
	        case vsc::dm::BinOp::BinOr:
	        case vsc::dm::BinOp::BinXor:
	        case vsc::dm::BinOp::LogAnd:
	        case vsc::dm::BinOp::LogOr:
	        case vsc::dm::BinOp::LogXor:
	        case vsc::dm::BinOp::Sll:
	        case vsc::dm::BinOp::Srl:
                e->lhs()->accept(m_this);
                break;
        }
    }


private:
    IContext                    *m_ctxt;
    vsc::dm::IDataType          *m_type;

};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


