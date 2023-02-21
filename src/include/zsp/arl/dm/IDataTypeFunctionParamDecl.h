/**
 * IDataTypeFunctionParamDecl.h
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
#include <string>
#include "vsc/dm/IDataType.h"
#include "vsc/dm/ITypeExpr.h"
#include "zsp/arl/dm/ITypeProcStmtVarDecl.h"

namespace zsp {
namespace arl {
namespace dm {

enum class ParamDir {
    In,
    Out,
    InOut
};

class IDataTypeFunctionParamDecl;
using IDataTypeFunctionParamDeclUP=vsc::dm::UP<IDataTypeFunctionParamDecl>;
class IDataTypeFunctionParamDecl : public virtual ITypeProcStmtVarDecl {
public:

    virtual ~IDataTypeFunctionParamDecl() { }

    virtual ParamDir getDirection() const = 0;

};

}
}
}


