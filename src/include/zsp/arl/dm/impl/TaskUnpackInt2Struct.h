/**
 * TaskUnpackInt2Struct.h
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
#include "dmgr/IDebugMgr.h"
#include "dmgr/impl/DebugMacros.h"
#include "vsc/dm/impl/ValRefBool.h"
#include "vsc/dm/impl/ValRefStruct.h"
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {



class TaskUnpackInt2Struct : public virtual VisitorBase {
public:

    TaskUnpackInt2Struct(
        dmgr::IDebugMgr     *dmgr,
        IContext            *ctxt) : m_dbg(0), m_ctxt(ctxt) { 
        DEBUG_INIT("zsp::arl::dm::TaskUnpackInt2Struct", dmgr);
    }

    virtual ~TaskUnpackInt2Struct() { }

    vsc::dm::ValRef unpack(
        const vsc::dm::ValRef       &val_i,
        vsc::dm::IDataTypeStruct    *dst_t) {
        DEBUG_ENTER("unpack val_i=0x%08x", vsc::dm::ValRefInt(val_i).get_val_u());
        vsc::dm::ValRefStruct val_s(m_ctxt->mkValRefStruct(dst_t));
        m_bit = 0;
        m_val_i = val_i;
        m_val_result_s.clear();
        m_val_result_s.push_back(val_s);
        dst_t->accept(m_this);
        DEBUG("val_s[0]=0x%08x", vsc::dm::ValRefInt(val_s.getFieldRef(0)).get_val_u());
        DEBUG("val_s[1]=0x%08x", vsc::dm::ValRefInt(val_s.getFieldRef(1)).get_val_u());
        DEBUG_LEAVE("unpack");
        return val_s;
    }

	virtual void visitDataTypeBool(vsc::dm::IDataTypeBool *t) override { 
        DEBUG_ENTER("visitDataTypeBool");
        vsc::dm::ValRefBool val(m_val_result_s.back());
        val.set_val((m_val_i.get_val_u() >> m_bit) & 1);

        m_bit += 1;
        DEBUG_LEAVE("visitDataTypeBool");
    }

	virtual void visitDataTypeEnum(vsc::dm::IDataTypeEnum *t) override { 
        DEBUG_ENTER("visitDataTypeEnum");
        vsc::dm::ValRefInt val(m_val_result_s.back());
        val.set_val((m_val_i.get_val_u() >> m_bit) & 0xFFFFFFFF);

        m_bit += 32;
        DEBUG_LEAVE("visitDataTypeEnum");
    }

	virtual void visitDataTypeInt(vsc::dm::IDataTypeInt *t) override { 
        DEBUG_ENTER("visitDataTypeInt width=%d", t->getWidth());
        vsc::dm::ValRefInt val(m_val_result_s.back());
        if (t->width() == 64) {
            val.set_val((m_val_i.get_val_u() >> m_bit));
        } else {
            uint64_t ival = (m_val_i.get_val_u() >> m_bit) & (1ULL << t->getWidth())-1;
            DEBUG("set_val: 0x%08x", ival);
            val.set_val(ival);
            DEBUG("get_val: 0x%08x", val.get_val_u());
        }

        m_bit += t->getWidth();
        DEBUG_LEAVE("visitDataTypeInt width=%d", t->getWidth());
    }

	virtual void visitDataTypeStruct(vsc::dm::IDataTypeStruct *t) override {
        DEBUG_ENTER("visitDataTypeStruct");

        vsc::dm::ValRefStruct val_s(m_val_result_s.back());
        for (uint32_t i=0; i<t->getFields().size(); i++) {
            m_val_result_s.push_back(val_s.getFieldRef(i));
            t->getFields().at(i)->getDataType()->accept(m_this);
            m_val_result_s.pop_back();
        }

        DEBUG_LEAVE("visitDataTypeStruct");
    }


private:
    dmgr::IDebug                      *m_dbg;
    IContext                          *m_ctxt;
    uint32_t                          m_bit;
    vsc::dm::ValRefInt                m_val_i;
    std::vector<vsc::dm::ValRef>      m_val_result_s;

};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


