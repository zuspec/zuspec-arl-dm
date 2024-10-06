/*
 * TypeProcStmtScope.cpp
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

#include "zsp/arl/dm/IVisitor.h"
#include "TypeProcStmtScope.h"


namespace zsp {
namespace arl {
namespace dm {



TypeProcStmtScope::TypeProcStmtScope(IContext *ctxt) : m_ctxt(ctxt) {

}

TypeProcStmtScope::TypeProcStmtScope(
    IContext                            *ctxt,
    const std::vector<ITypeProcStmt *>  &stmts) : m_ctxt(ctxt) {
    for (std::vector<ITypeProcStmt *>::const_iterator
        it=stmts.begin();
        it!=stmts.end(); it++) {
        addStatement(*it);
    }
}

TypeProcStmtScope::~TypeProcStmtScope() {

}

void TypeProcStmtScope::addStatement(ITypeProcStmt *stmt) {
    m_statements.push_back(ITypeProcStmtUP(stmt));
}

void TypeProcStmtScope::insertStatement(
        int32_t                 i,
        ITypeProcStmt           *stmt) {
    m_statements.insert(
        m_statements.begin()+i,
        ITypeProcStmtUP(stmt));
}

int32_t TypeProcStmtScope::addVariable(vsc::dm::ITypeVar *v, bool owned) {
    m_statements.push_back(ITypeProcStmtUP(dynamic_cast<ITypeProcStmt *>(v)));
    int32_t ret = m_variables.size();
    m_variables.push_back(vsc::dm::ITypeVarUP(v, false));
    if (!m_locals_t) {
        m_locals_t = vsc::dm::IDataTypeStructUP(m_ctxt->mkDataTypeStruct(""));
    }
    m_locals_t->addField(m_ctxt->mkTypeFieldPhy(
        v->name(),
        v->getDataType(),
        false,
        vsc::dm::TypeFieldAttr::NoAttr, 
        0 // ->getInit()
    ));

    return ret;
}

int32_t TypeProcStmtScope::insertVariable(
        int32_t                 i,
        ITypeProcStmtVarDecl    *v) {
    m_statements.insert(
        m_statements.begin()+i,
        ITypeProcStmtUP(v));
    int32_t ret = m_variables.size();
    m_variables.push_back(vsc::dm::ITypeVarUP(v, false));
    return ret;
}

void TypeProcStmtScope::accept(vsc::dm::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitTypeProcStmtScope(this);
    }
}

}
}
}
