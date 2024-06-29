/**
 * TaskGetTypeBitWidth.h
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
#include "zsp/arl/dm/impl/VisitorBase.h"
#include "vsc/dm/IDataTypeStruct.h"
namespace zsp {
namespace arl {
namespace dm {


class TaskGetTypeBitWidth :
    public virtual VisitorBase {
public:

    TaskGetTypeBitWidth() { }

    virtual ~TaskGetTypeBitWidth() { }

    int32_t width(vsc::dm::IDataType *t) {
        m_width = 0;
        t->accept(m_this);
        return m_width;
    }

    virtual void visitDataTypeBool(vsc::dm::IDataTypeBool *t) {
        m_width += 1;
    }

    virtual void visitDataTypeInt(vsc::dm::IDataTypeInt *t) {
        m_width += t->getWidth();
    }

    virtual void visitDataTypePackedStruct(IDataTypePackedStruct *t) {
        for (std::vector<vsc::dm::ITypeFieldUP>::const_iterator
            it=t->getFields().begin();
            it!=t->getFields().end(); it++) {
            (*it)->getDataType()->accept(m_this);
        }
    }

    virtual void visitDataTypeStruct(vsc::dm::IDataTypeStruct *t) {
        m_width += 8*t->getByteSize();
    }

    virtual void visitDataTypeWrapper(vsc::dm::IDataTypeWrapper *t) {
        t->getDataTypeVirt()->accept(m_this);
    }

private:
    int32_t     m_width;

};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


