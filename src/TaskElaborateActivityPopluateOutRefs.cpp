/*
 * TaskElaborateActivityPopluateOutRefs.cpp
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
#include "TaskElaborateActivityPopluateOutRefs.h"

namespace arl {


TaskElaborateActivityPopluateOutRefs::TaskElaborateActivityPopluateOutRefs(
    vsc::IModelBuildContext *ctxt) : m_ctxt(ctxt) {

}

TaskElaborateActivityPopluateOutRefs::~TaskElaborateActivityPopluateOutRefs() {

}

void TaskElaborateActivityPopluateOutRefs::visitModelActivityTraverse(IModelActivityTraverse *a) {
    a->getTarget()->accept(m_this);

    if (a->getActivity()) {
        a->getActivity()->accept(m_this);
    }
}

void TaskElaborateActivityPopluateOutRefs::visitModelFieldRef(vsc::IModelFieldRef *f) {

}

void TaskElaborateActivityPopluateOutRefs::visitModelFieldRefType(vsc::IModelFieldTypeRef *f) {
    if (!f->getRef()) {
        m_active_ref = f;
        f->getTypeField()->accept(m_this);
        m_active_ref = 0;
    }
}

void TaskElaborateActivityPopluateOutRefs::visitTypeFieldClaim(ITypeFieldClaim *f) {

}

void TaskElaborateActivityPopluateOutRefs::visitTypeFieldInOut(ITypeFieldInOut *f) {
    if (m_active_ref) {
        // TODO: use full path to name?
        vsc::IModelField *obj = f->getDataType()->mkRootField(m_ctxt, "xxxx", false);
        m_active_ref->setRef(obj);
        m_objs->push_back(vsc::IModelFieldUP(obj));
    }
}

}
