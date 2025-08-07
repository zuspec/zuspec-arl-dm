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
#include "zsp/arl/dm/IDataTypeTransparentAddrSpace.h"
#include "zsp/arl/dm/IDataTypeCoreLibComponent.h"
#include "zsp/arl/dm/IDataTypePureComponent.h"
#include "zsp/arl/dm/IDataTypeReg.h"

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

void VisitorProxy::visitDataTypeArlStruct(IDataTypeArlStruct *t) {
    VisitorProxy_visitDataTypeArlStruct(m_obj, t);
}

void VisitorProxy::visitDataTypeAddrClaim(IDataTypeAddrClaim *t) {
    VisitorProxy_visitDataTypeAddrClaim(m_obj, t);
}

void VisitorProxy::visitDataTypeAddrClaimTransparent(IDataTypeAddrClaimTransparent *t) {
    VisitorProxy_visitDataTypeAddrClaimTransparent(m_obj, t);
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

void VisitorProxy::visitDataTypePyObj(IDataTypePyObj *t) {
    VisitorProxy_visitDataTypePyObj(m_obj, t);
}

void VisitorProxy::visitDataTypeResource(IDataTypeResource *t) {
    VisitorProxy_visitDataTypeResource(m_obj, t);
}

void VisitorProxy::visitDataTypeTransparentAddrSpace(IDataTypeTransparentAddrSpace *t) {
    VisitorProxy_visitDataTypeTransparentAddrSpace(m_obj, t);
}

void VisitorProxy::visitDataTypeCoreLibComponent(IDataTypeCoreLibComponent *t) {
    VisitorProxy_visitDataTypeCoreLibComponent(m_obj, t);
}

void VisitorProxy::visitDataTypePureComponent(IDataTypePureComponent *t) {
    VisitorProxy_visitDataTypePureComponent(m_obj, t);
}

void VisitorProxy::visitDataTypeReg(IDataTypeReg *t) {
    VisitorProxy_visitDataTypeReg(m_obj, t);
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

void VisitorProxy::visitTypeProcStmtScope(ITypeProcStmtScope *s) {
    VisitorProxy_visitTypeProcStmtScope(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtAssign(ITypeProcStmtAssign *s) {
    VisitorProxy_visitTypeProcStmtAssign(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtBreak(ITypeProcStmtBreak *s) {
    VisitorProxy_visitTypeProcStmtBreak(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtContinue(ITypeProcStmtContinue *s) {
    VisitorProxy_visitTypeProcStmtContinue(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtExpr(ITypeProcStmtExpr *s) {
    VisitorProxy_visitTypeProcStmtExpr(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtForeach(ITypeProcStmtForeach *s) {
    VisitorProxy_visitTypeProcStmtForeach(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtIfClause(ITypeProcStmtIfClause *s) {
    VisitorProxy_visitTypeProcStmtIfClause(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtIfElse(ITypeProcStmtIfElse *s) {
    VisitorProxy_visitTypeProcStmtIfElse(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtMatch(ITypeProcStmtMatch *s) {
    VisitorProxy_visitTypeProcStmtMatch(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtRepeat(ITypeProcStmtRepeat *s) {
    VisitorProxy_visitTypeProcStmtRepeat(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtRepeatWhile(ITypeProcStmtRepeatWhile *s) {
    VisitorProxy_visitTypeProcStmtRepeatWhile(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtReturn(ITypeProcStmtReturn *s) {
    VisitorProxy_visitTypeProcStmtReturn(m_obj, s);
}

void VisitorProxy::visitTypeProcStmtYield(ITypeProcStmtYield *s) {
    VisitorProxy_visitTypeProcStmtYield(m_obj, s);
}

}
}
}
