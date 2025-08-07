/**
 * IDataTypeReg.h
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
#include <stdint.h>
#include "zsp/arl/dm/IDataTypePackedStruct.h"
#include "zsp/arl/dm/IDataTypePureComponent.h"

namespace zsp {
namespace arl {
namespace dm {

enum class RegAccess {
    NoAccess = 0,
    RW = 1,
    RO = 2,
    WO = 3,
    W1 = 4,
    CLR = 5,
    SET = 6
};

class IDataTypeReg : public virtual IDataTypePureComponent {
public:

    virtual ~IDataTypeReg() { }

    virtual IDataTypePackedStruct *getDataType() const = 0;

    virtual uint32_t getOffset() const = 0;

    virtual uint32_t getWidth() const = 0;
    
    virtual RegAccess getAccess() const = 0;

};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */
