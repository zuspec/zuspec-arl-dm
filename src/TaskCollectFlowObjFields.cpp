/*
 * TaskCollectFlowObjFields.cpp
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
#include "TaskCollectFlowObjFields.h"


namespace zsp {
namespace arl {
namespace dm {

TaskCollectFlowObjFields::TaskCollectFlowObjFields(
    std::vector<vsc::dm::IModelField *>     &fields) : m_fields(fields) {
    m_is_flowobj = false;
}

TaskCollectFlowObjFields::~TaskCollectFlowObjFields() {

}

void TaskCollectFlowObjFields::collect(vsc::dm::IModelField *action) {
    action->accept(m_this);
}

void TaskCollectFlowObjFields::visitDataTypeFlowObj(IDataTypeFlowObj *t) {
    m_is_flowobj = true;
}

void TaskCollectFlowObjFields::visitModelFieldRef(vsc::dm::IModelFieldRef *f) {
    m_is_flowobj = false;
    f->getDataType()->accept(m_this);

    if (m_is_flowobj) {
        m_fields.push_back(f);
    }
}

}
}
}
