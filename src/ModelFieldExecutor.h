/**
 * ModelFieldExecutor.h
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
#include "arl/IModelFieldExecutor.h"
#include "ModelField.h"

namespace arl {



class ModelFieldExecutor : public virtual IModelFieldExecutor, public virtual ModelField {
public:
    ModelFieldExecutor(
        const std::string   &name,
        vsc::IDataType      *type);

    virtual ~ModelFieldExecutor();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual vsc::IDataType *getDataType() const override {
        return m_type;
    }

    virtual void accept(vsc::IVisitor *v) override;

private:
    std::string             m_name;
    vsc::IDataType          *m_type;

};

}


