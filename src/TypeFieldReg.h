/**
 * TypeFieldReg.h
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
#include "zsp/arl/dm/ITypeFieldReg.h"
#include "TypeField.h"

namespace zsp {
namespace arl {
namespace dm {



class TypeFieldReg : 
    public virtual ITypeFieldReg,
    public virtual TypeField {
public:
    TypeFieldReg(
        const std::string   &name,
        vsc::dm::IDataType  *type,
        bool                owned
    );

    virtual int64_t getOffset() override {
        return m_offset;
    }

    virtual void setOffset(int64_t off) override {
        m_offset = off;
    }

    virtual int32_t getWidth() const override {
        return m_width;
    }

    virtual ~TypeFieldReg();

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    int64_t                 m_offset;
    int32_t                 m_width;

};

}
}
}


