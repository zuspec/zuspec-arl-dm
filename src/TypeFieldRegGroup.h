/**
 * TypeFieldRegGroup.h
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
#include "vsc/dm/IVisitor.h"
#include "zsp/arl/dm/ITypeFieldRegGroup.h"
#include "TypeField.h"

namespace zsp {
namespace arl {
namespace dm {



class TypeFieldRegGroup :
    public virtual ITypeFieldRegGroup,
    public virtual TypeField {
public:
    TypeFieldRegGroup(
        const std::string       &name,
        vsc::dm::IDataType      *type,
        bool                    owned);

    virtual ~TypeFieldRegGroup();

    virtual int32_t getByteSize() const override;

	virtual vsc::dm::IModelField *mkModelField(
		vsc::dm::IModelBuildContext 	*ctxt,
        const vsc::dm::ValRef           &val) override;
    
    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    int64_t                     m_offset;


};

}
}
}


