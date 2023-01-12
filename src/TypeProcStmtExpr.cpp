/*
 * TypeProcStmtExpr.cpp
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
#include "TypeProcStmtExpr.h"


namespace zsp {
namespace arl {
namespace dm {


TypeProcStmtExpr::TypeProcStmtExpr(vsc::dm::ITypeExpr *e) : m_expr(e) {

}

TypeProcStmtExpr::~TypeProcStmtExpr() {

}

void TypeProcStmtExpr::accept(vsc::dm::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitTypeProcStmtExpr(this);
    }

}

}
}
}
