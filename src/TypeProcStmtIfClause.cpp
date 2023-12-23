/*
 * TypeProcStmtIfClause.cpp
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
#include "zsp/arl/dm/IVisitor.h"
#include "TypeProcStmtIfClause.h"


namespace zsp {
namespace arl {
namespace dm {


TypeProcStmtIfClause::TypeProcStmtIfClause(
        vsc::dm::ITypeExpr          *cond,
        ITypeProcStmt               *stmt) :
        m_cond(cond), m_stmt(stmt) {

}

TypeProcStmtIfClause::~TypeProcStmtIfClause() {

}

void TypeProcStmtIfClause::accept(vsc::dm::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitTypeProcStmtIfClause(this);
    }
}

}
}
}
