/**
 * DataTypeResource.h
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
#include "zsp/arl/dm/IDataTypeResource.h"
#include "DataTypeArlStruct.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypeResource : 
    public virtual IDataTypeResource, 
    public virtual DataTypeArlStruct {
public:
    DataTypeResource(
        IContext            *ctxt,
        const std::string   &name);

    virtual ~DataTypeResource();

	virtual FlowObjKindE kind() const override { return FlowObjKindE::Resource; }

    virtual vsc::dm::ITypeField *getInstanceId() const override {
        return m_instance_id;
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    vsc::dm::ITypeField             *m_instance_id;
    vsc::dm::ITypeField             *m_initial;

};

}
}
}

