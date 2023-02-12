/*
 * TaskPopulateResourcePools.cpp
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
#include <stdio.h>
#include "vsc/dm/impl/ModelBuildContext.h"
#include "vsc/dm/impl/TaskSetUsedRand.h"
#include "DebugMacros.h"
#include "TaskPopulateResourcePools.h"


namespace zsp {
namespace arl {
namespace dm {

TaskPopulateResourcePools::TaskPopulateResourcePools(IContext *ctxt) : 
        m_ctxt(ctxt), m_pool(0) {
    DEBUG_INIT("TaskPopulateResourcePools");
}

TaskPopulateResourcePools::~TaskPopulateResourcePools() {

}

void TaskPopulateResourcePools::populate(IModelFieldComponent *root) {
    DEBUG_ENTER("populate");
    root->accept(m_this);
    DEBUG_LEAVE("populate");
}

void TaskPopulateResourcePools::visitModelFieldComponent(
        IModelFieldComponent *f) {
    for (std::vector<vsc::dm::IModelFieldUP>::const_iterator
        it=f->getFields().begin();
        it!=f->getFields().end(); it++) {
        (*it)->accept(m_this);
    }
}

void TaskPopulateResourcePools::visitModelFieldPool(IModelFieldPool *f) {
    DEBUG_ENTER("VisitModelFieldPool %s", f->name().c_str());
    m_pool = f;
    f->getDataTypePool()->accept(m_this);
    m_pool = 0;
    DEBUG_LEAVE("VisitModelFieldPool %s", f->name().c_str());
}

void TaskPopulateResourcePools::visitDataTypeResource(IDataTypeResource *t) {
    DEBUG_ENTER("visitDataTypeResource %s (pool=%p)", t->name().c_str(), m_pool);
    vsc::dm::ModelBuildContext build_ctxt(m_ctxt);

    if (m_pool) {
        int32_t sz = m_pool->getField(0)->val()->val_i();
        DEBUG("Pool size: %d", sz);
        for (uint32_t i=0; i<sz; i++) {
            char tmp[64];
            snprintf(tmp, sizeof(tmp), "%s[%d]", m_pool->name().c_str(), t->name().c_str());
            vsc::dm::IModelField *obj = t->mkRootField(
                &build_ctxt,
                tmp,
                false);
            obj->getField(0)->setFlags(vsc::dm::ModelFieldFlag::Resolved);
            obj->getField(0)->val()->set_val_i(i);
            vsc::dm::TaskSetUsedRand().apply(obj, true);
            m_pool->addObject(obj);
        }
    }

    DEBUG_LEAVE("visitDataTypeResource %s (pool=%p)", t->name().c_str(), m_pool);
}

}
}
}
