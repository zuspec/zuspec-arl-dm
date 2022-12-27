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
#include "zsp/arl/dm/IModelFieldPool.h"
#include "vsc/dm/IDataType.h"
#include "ModelField.h"

namespace zsp {
namespace arl {
namespace dm {



class ModelFieldPool : public virtual IModelFieldPool, public virtual ModelField {
public:
    ModelFieldPool(
        const std::string       &name,
        vsc::dm::IDataType          *type);

    virtual ~ModelFieldPool();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual vsc::dm::IDataType *getDataType() const override {
        return m_type;
    }

    virtual vsc::dm::IDataType *getDataTypePool() const override {
        return m_type_pool;
    }
    
    virtual int32_t getId() const override { return m_id; }

    virtual void setId(int32_t id) override { m_id = id; }

    virtual void setDataTypePool(vsc::dm::IDataType *t) override {
        m_type_pool = t;
    }

    virtual void addObject(vsc::dm::IModelField *obj) override {
        m_objects.push_back(vsc::dm::IModelFieldUP(obj));
    }

    virtual const std::vector<vsc::dm::IModelFieldUP> &getObjects() const override {
        return m_objects;
    }

    virtual const std::pair<int32_t,int32_t> &getGlobalPoolRange() const override {
        return m_global_pool_range;
    }

    virtual void setGlobalPoolRange(int32_t i1, int32_t i2) override { }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    std::string                         m_name;
    vsc::dm::IDataType                      *m_type;
    vsc::dm::IDataType                      *m_type_pool;
    int32_t                             m_id;

    // Objects are only used for resource pools
    std::vector<vsc::dm::IModelFieldUP>     m_objects;

    // Stores the range that this pool holds within
    // the global per-type object pool
    std::pair<int32_t,int32_t>          m_global_pool_range;

};

}
}
}

