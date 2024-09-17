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
#include "vsc/dm/IAssociatedData.h"
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

enum class DataTypeFunctionFlags {
    NoFlags = 0,
    Solve   = (1 << 0),
    Target  = (1 << 1), // Target function
    Blocks  = (1 << 2), // Blocking target function
    Core    = (1 << 3),
    Context = (1 << 4), // Non-static member of a containing type
    Import  = (1 << 5),
    Export  = (1 << 6),
};

static inline DataTypeFunctionFlags operator | (const DataTypeFunctionFlags lhs, const DataTypeFunctionFlags rhs) {
        return static_cast<DataTypeFunctionFlags>(
                        static_cast<uint32_t>(lhs) | static_cast<uint32_t>(rhs));
}

static inline DataTypeFunctionFlags operator & (const DataTypeFunctionFlags lhs, const DataTypeFunctionFlags rhs) {
        return static_cast<DataTypeFunctionFlags>(
                        static_cast<uint32_t>(lhs) & static_cast<uint32_t>(rhs));
}

static inline DataTypeFunctionFlags operator ~ (const DataTypeFunctionFlags lhs) {
        return static_cast<DataTypeFunctionFlags>(~static_cast<uint32_t>(lhs));
}

class IDataTypeFunction;
using IDataTypeFunctionUP=vsc::dm::UP<IDataTypeFunction>;
class IDataTypeFunction : 
    public virtual vsc::dm::IAccept {
public:

    virtual ~IDataTypeFunction() { }

    virtual const std::string &name() const = 0;

    virtual vsc::dm::IDataType *getReturnType() const = 0;

    virtual const std::vector<IDataTypeFunctionParamDecl *> &getParameters() const = 0;

    virtual void addParameter(IDataTypeFunctionParamDecl *p) = 0;

    // Returns the data type of the parameters frame
    virtual vsc::dm::IDataTypeStruct *getParametersType() const = 0;

    // Appears to not be used
    virtual ITypeProcStmtDeclScope *getParamScope() = 0;

    virtual vsc::dm::IDataTypeStruct *getContext() const = 0;

    virtual bool getIsExport() const = 0;

    virtual void setIsExport(bool e) = 0;

    virtual ITypeProcStmtScope *getBody() const = 0;

    virtual const std::vector<IDataTypeFunctionImportUP> &getImportSpecs() const = 0;

    virtual void addImportSpec(IDataTypeFunctionImport *spec) = 0;

    virtual DataTypeFunctionFlags getFlags() const = 0;

    virtual void setFlags(DataTypeFunctionFlags flags) = 0;

    virtual bool hasFlags(DataTypeFunctionFlags f) const = 0;

    virtual void clrFlags(DataTypeFunctionFlags f) = 0;

    virtual void setAssociatedData(vsc::dm::IAssociatedData *data) = 0;

    virtual vsc::dm::IAssociatedData *getAssociatedData() const = 0;

};

}
}
}


