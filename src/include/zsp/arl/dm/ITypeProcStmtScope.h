/**
 * ITypeProcStmtScope.h
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
#include <memory>
#include <vector>
#include "zsp/arl/dm/ITypeProcStmt.h"
#include "zsp/arl/dm/ITypeProcStmtDeclScope.h"

namespace zsp {
namespace arl {
namespace dm {


class ITypeProcStmtScope;
using ITypeProcStmtScopeUP=vsc::dm::UP<ITypeProcStmtScope>;
class ITypeProcStmtScope : 
    public virtual ITypeProcStmtDeclScope,
    public virtual ITypeProcStmt {
public:

    virtual ~ITypeProcStmtScope() { }

    virtual void addStatement(ITypeProcStmt *stmt, bool owned=true) = 0;

    virtual void insertStatement(
        int32_t             i,
        ITypeProcStmt       *s) = 0;

    virtual int32_t insertVariable(
        int32_t                 i,
        ITypeProcStmtVarDecl    *s) = 0;

    virtual const std::vector<ITypeProcStmtUP> &getStatements() const = 0;

    virtual vsc::dm::IDataTypeStruct *getLocalsT() const = 0;

};

}
}
}


