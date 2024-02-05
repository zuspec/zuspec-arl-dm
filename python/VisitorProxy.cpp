/*
 * VisitorProxy.cpp
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

#include "VisitorProxy.h"
#include "core.h"


namespace zsp {
namespace arl {
namespace dm {

VisitorProxy::VisitorProxy(PyObject *obj) : VisitorBase(false), m_obj(obj) {
    Py_INCREF(m_obj);
}

VisitorProxy::~VisitorProxy() {
    Py_DECREF(m_obj);
}

void VisitorProxy::visitDataTypeAction(IDataTypeAction *t) {
    VisitorProxy_visitDataTypeAction(m_obj, t);
}

void VisitorProxy::visitDataTypeAddrHandle(IDataTypeAddrHandle *t) {
    VisitorProxy_visitDataTypeAddrHandle(m_obj, t);
}

void VisitorProxy::visitDataTypeComponent(IDataTypeComponent *t) {
    VisitorProxy_visitDataTypeComponent(m_obj, t);
}

void VisitorProxy::visitDataTypeFlowObj(IDataTypeFlowObj *t) {
    VisitorProxy_visitDataTypeFlowObj(m_obj, t);
}

void VisitorProxy::visitDataTypeFunction(IDataTypeFunction *t) {
    VisitorProxy_visitDataTypeFunction(m_obj, t);
}

void VisitorProxy::visitDataTypePackedStruct(IDataTypePackedStruct *t) {
    VisitorProxy_visitDataTypePackedStruct(m_obj, t);
}

void VisitorProxy::visitModelFieldAction(IModelFieldAction *f) {
    VisitorProxy_visitModelFieldAction(m_obj, f);
}

void VisitorProxy::visitModelFieldComponent(IModelFieldComponent *f) {
    VisitorProxy_visitModelFieldComponent(m_obj, f);
}

void VisitorProxy::visitModelFieldComponentRoot(IModelFieldComponentRoot *f) {
    VisitorProxy_visitModelFieldComponentRoot(m_obj, f);
}

void VisitorProxy::visitModelFieldPool(IModelFieldPool *f) {
    VisitorProxy_visitModelFieldPool(m_obj, f);
}

void VisitorProxy::visitTypeFieldReg(ITypeFieldReg *f) {
    VisitorProxy_visitTypeFieldReg(m_obj, f);
}

}
}
}
