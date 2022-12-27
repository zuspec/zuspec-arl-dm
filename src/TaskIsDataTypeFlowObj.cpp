/*
 * TaskIsDataTypeFlowObj.cpp
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
#include "TaskIsDataTypeFlowObj.h"


namespace zsp {
namespace arl {
namespace dm {


TaskIsDataTypeFlowObj::TaskIsDataTypeFlowObj() : 
    m_ret(false), m_check_kind(false), m_kind(FlowObjKindE::Resource) {

}

TaskIsDataTypeFlowObj::TaskIsDataTypeFlowObj(FlowObjKindE kind) : 
    m_ret(false), m_check_kind(true), m_kind(kind) {

}

TaskIsDataTypeFlowObj::~TaskIsDataTypeFlowObj() {

}

bool TaskIsDataTypeFlowObj::test(vsc::IDataType *t) {
    TaskIsDataTypeFlowObj task;
    t->accept(&task);
    return task.m_ret;
}

bool TaskIsDataTypeFlowObj::test(FlowObjKindE kind, vsc::IDataType *t) {
    TaskIsDataTypeFlowObj task(kind);
    t->accept(&task);
    return task.m_ret;
}

void TaskIsDataTypeFlowObj::visitDataTypeFlowObj(IDataTypeFlowObj *t) {
    if (m_check_kind) {
        m_ret = (t->kind() == m_kind);
    } else {
        m_ret = true;
    }
}

}
}
}
