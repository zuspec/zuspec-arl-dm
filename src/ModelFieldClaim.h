/**
 * ModelFieldClaim.h
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
#include "arl/IModelFieldClaim.h"
#include "arl/ITypeFieldClaim.h"
#include "ModelField.h"

namespace arl {



class ModelFieldClaim : public virtual IModelFieldClaim, public virtual ModelField {
public:
    ModelFieldClaim(ITypeFieldClaim *type);

    virtual ~ModelFieldClaim();

    virtual const std::string &name() const override {
        return m_type->name();
    }

    virtual vsc::IDataType *getDataType() const override {
        return m_type->getDataType();
    }

	virtual void setRef(vsc::IModelField *ref) override {
        m_ref = ref;
    }

	virtual vsc::IModelField *getRef() const override {
        return m_ref;
    }

private:
    ITypeFieldClaim                 *m_type;
    vsc::IModelField                *m_ref;
};

}


