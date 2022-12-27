/**
 * ModelFieldExecutorClaim.h
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
#include <string>
#include "zsp/arl/dm/IModelFieldExecutorClaim.h"
#include "ModelField.h"

namespace zsp {
namespace arl {
namespace dm {



class ModelFieldExecutorClaim : public virtual IModelFieldExecutorClaim, public virtual ModelField  {
public:

    ModelFieldExecutorClaim(
        const std::string       &name,
        vsc::dm::IDataType          *claim_t);

    virtual ~ModelFieldExecutorClaim();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual vsc::dm::IDataType *getDataType() const override {
        return m_type;
    }

    virtual vsc::dm::IModelField *getRef() const override {
        return m_ref;
    }

    virtual void setRef(vsc::dm::IModelField *f) override {
        m_ref = f;
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    std::string                 m_name;
    vsc::dm::IDataType              *m_type;
    vsc::dm::IModelField            *m_ref;

};

}
}
}


