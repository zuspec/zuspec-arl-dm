/*
 * ModelFieldPool.cpp
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
#include "arl/IVisitor.h"
#include "ModelFieldPool.h"


namespace zsp {
namespace arl {
namespace dm {

ModelFieldPool::ModelFieldPool(
    const std::string       &name,
    vsc::IDataType          *type) : m_name(name), m_type(type), m_type_pool(0) {

}

ModelFieldPool::~ModelFieldPool() {

}

void ModelFieldPool::accept(vsc::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitModelFieldPool(this);
    } else if (v->cascade()) {
        v->visitModelField(this);
    }

}

}
}
}
