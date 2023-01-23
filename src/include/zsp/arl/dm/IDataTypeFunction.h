/**
 * IDataTypeFunction.h
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
#include <vector>
#include "vsc/dm/IDataTypeStruct.h"
#include "zsp/arl/dm/IDataTypeFunctionImport.h"
#include "zsp/arl/dm/IDataTypeFunctionParamDecl.h"
#include "zsp/arl/dm/ITypeProcStmtDeclScope.h"
#include "zsp/arl/dm/ITypeProcStmtScope.h"
#include "vsc/dm/IAccept.h"
#include "vsc/dm/IDataType.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeFunction;
using IDataTypeFunctionUP=std::unique_ptr<IDataTypeFunction>;
class IDataTypeFunction : 
    public virtual ITypeProcStmtDeclScope,
    public virtual vsc::dm::IAccept {
public:

    virtual ~IDataTypeFunction() { }

    virtual const std::string &name() const = 0;

    virtual vsc::dm::IDataType *getReturnType() const = 0;

    virtual const std::vector<IDataTypeFunctionParamDecl *> &getParameters() const = 0;

    virtual void addParameter(IDataTypeFunctionParamDecl *p) = 0;

    virtual ITypeProcStmtScope *getParamScope() const = 0;

    virtual vsc::dm::IDataTypeStruct *getContext() const = 0;

    virtual bool getIsExport() const = 0;

    virtual void setIsExport(bool e) = 0;

    virtual ITypeProcStmtScope *getBody() const = 0;

    virtual const std::vector<IDataTypeFunctionImportUP> &getImportSpecs() const = 0;

    virtual void addImportSpec(IDataTypeFunctionImport *spec) = 0;

};

}
}
}


