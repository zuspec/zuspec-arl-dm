/*
 * TypeFieldReg.cpp
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
#include "zsp/arl/dm/IVisitor.h"
#include "TaskCalculateRegWidth.h"
#include "TypeFieldReg.h"


namespace zsp {
namespace arl {
namespace dm {


TypeFieldReg::TypeFieldReg(
    const std::string       &name,
    vsc::dm::IDataType      *type,
    bool                    owned) : 
        TypeField(name, type, owned, vsc::dm::TypeFieldAttr::NoAttr) {
    m_width = TaskCalculateRegWidth().width(type);
}

TypeFieldReg::~TypeFieldReg() {

}

void TypeFieldReg::accept(vsc::dm::IVisitor *v) {
    if (dynamic_cast<arl::dm::IVisitor *>(v)) {
        dynamic_cast<arl::dm::IVisitor *>(v)->visitTypeFieldReg(this);
    } else if (v->cascade()) {
        v->visitTypeField(this);
    }
}

}
}
}
