/**
 * ITypeProcStmtMatch.h
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
#include "arl/ITypeProcStmt.h"
#include "arl/ITypeProcStmtMatchChoice.h"
#include "vsc/ITypeExpr.h"

namespace arl {

class ITypeProcStmtMatch : public virtual ITypeProcStmt {
public:

    virtual ~ITypeProcStmtMatch() { }

    virtual vsc::ITypeExpr *getCond() const = 0;

    virtual ITypeProcStmt *getDefault() const = 0;

    virtual void setDefault(ITypeProcStmt *s) = 0;

    virtual void addChoice(ITypeProcStmtMatchChoice *choice) = 0;

    virtual const std::vector<ITypeProcStmtMatchChoiceUP> &getChoices() const = 0;


};

} /* namespace arl */


