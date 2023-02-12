/*
 * TaskVisitComponentFields.cpp
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
#include "TaskVisitComponentFields.h"


namespace zsp {
namespace arl {
namespace dm {



TaskVisitComponentFields::TaskVisitComponentFields(
    const std::function<void (int32_t, int32_t, IModelFieldComponent *)> &enter,
    const std::function<void (int32_t, int32_t, IModelFieldComponent *)> &leave)
    : m_depth(0), m_enter(enter), m_leave(leave) {

}

TaskVisitComponentFields::~TaskVisitComponentFields() {

}

void TaskVisitComponentFields::visit(IModelFieldComponent *comp) {
    m_depth = -1;
    m_idx = 0;
    comp->accept(m_this);
}

void TaskVisitComponentFields::visitModelField(vsc::dm::IModelField *f) {
    for (uint32_t i=0; i<f->getFields().size(); i++) {
        m_idx = i;
        f->getFields().at(i)->accept(m_this);
    }
}

void TaskVisitComponentFields::visitModelFieldComponent(IModelFieldComponent *f) {
    m_depth++;
    m_enter(m_depth, m_idx, f);
    visitModelField(f);
    m_leave(m_depth, m_idx, f);
    m_depth--;
}

}
}
}
