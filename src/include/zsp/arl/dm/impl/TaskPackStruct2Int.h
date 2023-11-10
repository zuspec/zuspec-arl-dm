/**
 * TaskPackStruct2Int.h
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
#include "vsc/dm/impl/ValRefInt.h"
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {



class TaskPackStruct2Int : public virtual VisitorBase {
public:

    TaskPackStruct2Int(IContext *ctxt) : m_ctxt(ctxt) { }

    virtual ~TaskPackStruct2Int() { }

    vsc::dm::ValRefInt pack(const vsc::dm::ValRef &v) {
        m_phase = 0;
        m_bits = 0;
        v.type()->accept(m_this);

    }

	virtual void visitDataTypeBool(vsc::dm::IDataTypeBool *t) override { 
        if (m_phase == 1) {
            // 
        }

        m_bits += 1;
    }

	virtual void visitDataTypeInt(vsc::dm::IDataTypeInt *t) override { 
        if (m_phase == 1) {
            // 
        }

        m_bits += t->width();
    }

	virtual void visitDataTypeStruct(vsc::dm::IDataTypeStruct *t) override {
        for (uint32_t i=0; i<t->getFields().size(); i++) {
            t->getField(i)->accept(m_this);
        }
    }

protected:
    IContext                    *m_ctxt;
    int32_t                     m_phase;
    int32_t                     m_bits;
    vsc::dm::ValRef             m_val;
    vsc::dm::ValRefInt          m_ival;
};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


