/**
 * ValRefActivity.h
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
#include "vsc/dm/impl/ValRefStruct.h"
#include "zsp/arl/dm/IDataTypeActivityScope.h"

namespace zsp {
namespace arl {
namespace dm {



class ValRefActivityScope : public vsc::dm::ValRefStruct {
public:

    ValRefActivityScope(const ValRef &rhs) : ValRefStruct(rhs) { }

    virtual ~ValRefActivityScope() { }

    int32_t getNumActivities() const {
        return dynamic_cast<IDataTypeActivityScope *>(type())->getActivities().size();
    }

    vsc::dm::ValRef getActivityRef(int32_t i) {
        char *ptr = reinterpret_cast<char *>(m_vp);
        IDataTypeActivityScope *scope = dynamic_cast<IDataTypeActivityScope *>(type());
        ITypeFieldActivity *activity = scope->getActivities().at(i).get();
        vsc::dm::ValRef::Flags flags = static_cast<ValRef::Flags>(
            static_cast<uint32_t>(m_flags) & ~static_cast<uint32_t>(ValRef::Flags::Owned));
        flags = flags | ValRef::Flags::IsPtr;
        int32_t offset = scope->getActivityOffset()+activity->getOffset();
        return vsc::dm::ValRef(
            reinterpret_cast<uintptr_t>(&ptr[offset]),
            field,
            flags
        );
    }

};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


