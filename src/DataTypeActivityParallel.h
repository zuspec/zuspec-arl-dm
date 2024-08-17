/**
 * DataTypeActivityParallel.h
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
#include "zsp/arl/dm/IDataTypeActivityParallel.h"
#include "DataTypeActivityScope.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypeActivityParallel : 
    public virtual IDataTypeActivityParallel,
    public virtual DataTypeActivityScope {
public:
    DataTypeActivityParallel();

    virtual ~DataTypeActivityParallel();

	virtual IModelActivity *mkActivity(
		vsc::dm::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) override;

    virtual vsc::dm::IDataTypeStruct *getSuper() override {
        return 0;
    }

    virtual void setSuper(vsc::dm::IDataTypeStruct *t, bool owned=false) override { }

    virtual void accept(vsc::dm::IVisitor *v) override;
};

}
}
}

