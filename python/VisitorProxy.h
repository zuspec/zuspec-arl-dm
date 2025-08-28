/**
 * VisitorProxy.h
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
#pragma once
#include <Python.h>
#include "zsp/arl/dm/impl/VisitorBase.h"
#include "zsp/arl/dm/IDataTypeTransparentAddrSpace.h"
#include "zsp/arl/dm/IDataTypeCoreLibComponent.h"
#include "zsp/arl/dm/IDataTypePureComponent.h"
#include "zsp/arl/dm/IDataTypeReg.h"

namespace zsp {
namespace arl {
namespace dm {


class VisitorProxy : public VisitorBase {
public:
    VisitorProxy(PyObject *);

    virtual ~VisitorProxy();

    virtual void visitDataTypeAction(IDataTypeAction *t) override;

	virtual void visitDataTypeArlStruct(IDataTypeArlStruct *t) override;

	virtual void visitDataTypeAddrClaim(IDataTypeAddrClaim *t) override;

	virtual void visitDataTypeAddrClaimTransparent(IDataTypeAddrClaimTransparent *t) override;

	virtual void visitDataTypeAddrHandle(IDataTypeAddrHandle *t) override;

    virtual void visitDataTypeComponent(IDataTypeComponent *t) override;

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override;

	virtual void visitDataTypeFunction(IDataTypeFunction *t) override;

	virtual void visitDataTypePackedStruct(IDataTypePackedStruct *t) override;

virtual void visitDataTypePyObj(IDataTypePyObj *t) override;

virtual void visitDataTypeResource(IDataTypeResource *t) override;

virtual void visitDataTypeTransparentAddrSpace(IDataTypeTransparentAddrSpace *t) override;

virtual void visitDataTypeCoreLibComponent(IDataTypeCoreLibComponent *t) override;

virtual void visitDataTypePureComponent(IDataTypePureComponent *t) override;

virtual void visitDataTypeReg(IDataTypeReg *t) override;

	virtual void visitModelFieldAction(IModelFieldAction *f) override;

	virtual void visitModelFieldComponent(IModelFieldComponent *f) override;

	virtual void visitModelFieldComponentRoot(IModelFieldComponentRoot *f) override;

	virtual void visitModelFieldPool(IModelFieldPool *f) override;

	virtual void visitTypeFieldReg(ITypeFieldReg *f) override;

    virtual void visitTypeFieldInOut(ITypeFieldInOut *f) override;

    virtual void visitTypeProcStmtScope(ITypeProcStmtScope *s) override;
    virtual void visitTypeProcStmtAssign(ITypeProcStmtAssign *s) override;
    virtual void visitTypeProcStmtBreak(ITypeProcStmtBreak *s) override;
    virtual void visitTypeProcStmtContinue(ITypeProcStmtContinue *s) override;
    virtual void visitTypeProcStmtExpr(ITypeProcStmtExpr *s) override;
    virtual void visitTypeProcStmtForeach(ITypeProcStmtForeach *s) override;
    virtual void visitTypeProcStmtIfClause(ITypeProcStmtIfClause *s) override;
    virtual void visitTypeProcStmtIfElse(ITypeProcStmtIfElse *s) override;
    virtual void visitTypeProcStmtMatch(ITypeProcStmtMatch *s) override;
    virtual void visitTypeProcStmtRepeat(ITypeProcStmtRepeat *s) override;
    virtual void visitTypeProcStmtRepeatWhile(ITypeProcStmtRepeatWhile *s) override;
    virtual void visitTypeProcStmtReturn(ITypeProcStmtReturn *s) override;
    virtual void visitTypeProcStmtYield(ITypeProcStmtYield *s) override;
    virtual void visitTypeExecProc(ITypeExecProc *t) override;

private:
    PyObject                *m_obj;

};

}
}
}
