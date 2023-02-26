/**
 * TaskIsDataTypeFlowObj.h
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
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {


class TaskIsDataTypeFlowObj : public VisitorBase {
public:
    TaskIsDataTypeFlowObj() : 
        m_ret(false), m_check_kind(false), m_kind(FlowObjKindE::Resource) {

    }

    TaskIsDataTypeFlowObj(FlowObjKindE kind) :
        m_ret(false), m_check_kind(true), m_kind(kind) {

    }

    virtual ~TaskIsDataTypeFlowObj() { }

    static bool test(vsc::dm::IDataType *t) {
        TaskIsDataTypeFlowObj task;
        t->accept(&task);
        return task.m_ret;
    }

    static bool test(FlowObjKindE kind, vsc::dm::IDataType *t) {
        TaskIsDataTypeFlowObj task(kind);
        t->accept(&task);
        return task.m_ret;
    }

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override {
        if (m_check_kind) {
            m_ret = (t->kind() == m_kind);
        } else {
            m_ret = true;
        }
    } 

private:
    bool                m_ret;
    bool                m_check_kind;
    FlowObjKindE        m_kind;

};

}
}
}

