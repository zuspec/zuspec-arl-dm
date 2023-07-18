/*
 * ModelFieldRegGroup.cpp
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
#include "zsp/arl/dm/IVisitor.h"
#include "ModelFieldRegGroup.h"


namespace zsp {
namespace arl {
namespace dm {


ModelFieldRegGroup::ModelFieldRegGroup(
    const std::string       &name,
    vsc::dm::IDataType      *type) : m_name(name), m_type(type), m_id(-1) {

}

ModelFieldRegGroup::~ModelFieldRegGroup() {

}

void ModelFieldRegGroup::accept(vsc::dm::IVisitor *v) {
    if (dynamic_cast<dm::IVisitor *>(v)) {
        dynamic_cast<dm::IVisitor *>(v)->visitModelFieldRegGroup(this);
    } else if (v->cascade()) {
        v->visitModelField(this);
    }
}

}
}
}
