/**
 * TypeFieldRegGroupArr.h
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
#include "zsp/arl/dm/ITypeFieldRegGroupArr.h"
#include "TypeFieldRegGroup.h"

namespace zsp {
namespace arl {
namespace dm {



class TypeFieldRegGroupArr :
    public virtual ITypeFieldRegGroupArr,
    public virtual TypeFieldRegGroup {
public:
    TypeFieldRegGroupArr(
        const std::string       &name,
        vsc::dm::IDataType      *type,
        bool                    own_type,
        vsc::dm::IDataType      *elem_type,
        bool                    own_elem_type,
        int32_t                 size);

    virtual ~TypeFieldRegGroupArr();

    virtual vsc::dm::IDataType *getElemType() override {
        return m_elem_type.get();
    }

    virtual int32_t getSize() override {
        return m_size;
    }

    virtual int32_t getStride() override {
        return m_stride;
    }

    virtual void setStride(int32_t s) override {
        m_stride = s;
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    vsc::dm::IDataTypeUP        m_elem_type;
    int32_t                     m_size;
    int32_t                     m_stride;

};

}
}
}


