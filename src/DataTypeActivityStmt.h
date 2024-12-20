/**
 * DataTypeActivityStmt.h
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
#include "vsc/dm/impl/ValRef.h"
#include "zsp/arl/dm/IDataTypeActivity.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypeActivityStmt : public virtual IDataTypeActivity {
public:
    DataTypeActivityStmt();

    virtual ~DataTypeActivityStmt();

    virtual void initVal(vsc::dm::ValRef &v) override { }

    virtual void finiVal(vsc::dm::ValRef &v) override { }

    virtual vsc::dm::ValRef copyVal(const vsc::dm::ValRef &v) override { 
        return vsc::dm::ValRef();
    }

	virtual void finalize(vsc::dm::IContext *ctxt) override { }

    virtual vsc::dm::IValIterator *mkValIterator(const vsc::dm::ValRef &src) override {
        return 0;
    }

    virtual vsc::dm::IValMutIterator *mkValMutIterator(const vsc::dm::ValRef &src) override {
        return 0;
    }

};

}
}
}


