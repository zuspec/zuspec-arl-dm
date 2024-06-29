/**
 * TaskGetSubField.h
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

namespace zsp {
namespace arl {
namespace dm {



class TaskGetSubField :
    public virtual VisitorBase {
public:

    TaskGetSubField(bool phy=false) : m_phy(phy) { }

    virtual ~TaskGetSubField() { }

    vsc::dm::ITypeField *get(vsc::dm::IDataType *base, int32_t idx) {
        m_struct = 0;
        base->accept(m_this);

        return (m_struct)?m_struct->getField(idx):0;
    }

	virtual void visitDataTypeAction(IDataTypeAction *i) override {
        m_struct = i;
    }

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override {
        m_struct = t;
    }

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override {
        m_struct = t;
    }

	virtual void visitDataTypeStruct(vsc::dm::IDataTypeStruct *t) override {
        m_struct = t;
    }

    virtual void visitDataTypeWrapper(vsc::dm::IDataTypeWrapper *t) override {
        if (m_phy) {
            t->getDataTypePhy()->accept(m_this);
        } else {
            t->getDataTypeVirt()->accept(m_this);
        }
    }

private:
    bool                        m_phy;
    vsc::dm::IDataTypeStruct    *m_struct;


};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


