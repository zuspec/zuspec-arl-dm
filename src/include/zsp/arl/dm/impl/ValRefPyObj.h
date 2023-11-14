/**
 * ValRefPyObj.h
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
#include "vsc/dm/impl/ValRefPtr.h"

namespace pyapi {
    struct PyEvalObj;
}

namespace zsp {
namespace arl {
namespace dm {



class ValRefPyObj : public virtual vsc::dm::ValRefPtr {
public:

    ValRefPyObj(const ValRef &rhs) : vsc::dm::ValRefPtr(rhs) {
        if (type()) {
            // Acquire the object
            type()->initVal(*this);
        }
    }

    virtual ~ValRefPyObj() {
        if (type()) {
            // Release the object
            type()->finiVal(*this);
        }
    }

    pyapi::PyEvalObj *getObj() const {
        return reinterpret_cast<pyapi::PyEvalObj *>(ValRefPtr::get_val());
    }

    void setObj(pyapi::PyEvalObj *obj) {
        // Release current object
        if (type() && get_val()) {
            type()->finiVal(*this);
        }

        set_val(reinterpret_cast<uintptr_t>(obj));

        // Acquire the new object 
        if (type() && get_val()) {
            type()->initVal(*this);
        }
    }

};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


