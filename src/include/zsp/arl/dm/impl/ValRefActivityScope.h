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
#include "zsp/arl/dm/IDataTypeActivity.h"

namespace zsp {
namespace arl {
namespace dm {



class ValRefActivity : public vsc::dm::ValRefStruct {
public:

    ValRefActivity(const ValRef &rhs) : ValRefStruct(rhs) { }

    virtual ~ValRefActivity() { }

    int32_t getNumActivities() const {
        return dynamic_cast<IDataTypeActivity *>(type())->getA

    }

    ValRef getActivityRef(int32_t)

};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


