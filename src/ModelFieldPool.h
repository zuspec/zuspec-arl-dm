/**
 * ModelFieldPool.h
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
#include <vector>
#include "arl/IModelFieldPool.h"
#include "vsc/IDataType.h"
#include "ModelField.h"

namespace arl {


class ModelFieldPool : public virtual IModelFieldPool, public virtual ModelField {
public:
    ModelFieldPool(
        const std::string       &name,
        vsc::IDataType          *type);

    virtual ~ModelFieldPool();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual vsc::IDataType *getDataType() const override {
        return m_type;
    }

    virtual vsc::IDataType *getDataTypePool() const override {
        return m_type_pool;
    }

    virtual void setDataTypePool(vsc::IDataType *t) override {
        m_type_pool = t;
    }

    virtual void addObject(vsc::IModelField *obj) override {
        m_objects.push_back(vsc::IModelFieldUP(obj));
    }

    virtual const std::vector<vsc::IModelFieldUP> &getObjects() const override {
        return m_objects;
    }

    virtual void accept(vsc::IVisitor *v) override;

private:
    std::string                         m_name;
    vsc::IDataType                      *m_type;
    vsc::IDataType                      *m_type_pool;
    std::vector<vsc::IModelFieldUP>     m_objects;

};

}

