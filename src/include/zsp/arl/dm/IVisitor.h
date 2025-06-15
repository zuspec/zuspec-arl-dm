/*
 * IVisitor.h
 *
 *  Created on: Apr 2, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IVisitor.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeAction;
class IDataTypeActivity;
class IDataTypeActivityBind;
class IDataTypeActivityParallel;
class IDataTypeActivityReplicate;
class IDataTypeActivitySchedule;
class IDataTypeActivitySequence;
class IDataTypeActivityTraverse;
class IDataTypeActivityTraverseType;
class IDataTypeAddrClaim;
class IDataTypeAddrClaimTransparent;
class IDataTypeAddrHandle;
class IDataTypeAddrSpaceC;
class IDataTypeAddrSpaceTransparentC;
class IDataTypeComponent;
class IDataTypeFlowObj;
class IDataTypeFunctionImport;
class IDataTypeFunction;
class IDataTypeFunctionParamDecl;
class IDataTypePackedStruct;
class IDataTypePyObj;
class IDataTypeRegGroup;
class IDataTypeResource;
class IDataTypeArlStruct;
class IModelActivityBind;
class IModelActivityParallel;
class IModelActivityReplicate;
class IModelActivitySchedule;
class IModelActivityScope;
class IModelActivitySequence;
class IModelActivityTraverse;
class IModelFieldAction;
class IModelFieldComponent;
class IModelFieldComponentRoot;
class IModelFieldExecutor;
class IModelFieldExecutorClaim;
class IModelFieldClaim;
class IModelFieldInOut;
class IModelFieldPool;
class IModelFieldRegGroup;
class ITypeExprMethodCallContext;
class ITypeExprMethodCallStatic;
class ITypeExec;
class ITypeExecProc;
class ITypeExprPyImportRef;
class ITypeExprPythonFieldRef;
class ITypeExprPythonMethodCall;
class ITypeExprPythonModuleRef;
class ITypeFieldActivity;
class ITypeFieldAddrClaim;
class ITypeFieldAddrClaimTransparent;
class ITypeFieldClaim;
class ITypeFieldExecutor;
class ITypeFieldExecutorClaim;
class ITypeFieldInOut;
class ITypeFieldPool;
class ITypeFieldReg;
class ITypeFieldRegGroup;
class ITypeFieldRegGroupArr;
class ITypeProcStmt;
class ITypeProcStmtAssign;
class ITypeProcStmtBreak;
class ITypeProcStmtContinue;
class ITypeProcStmtExpr;
class ITypeProcStmtForeach;
class ITypeProcStmtIfClause;
class ITypeProcStmtIfElse;
class ITypeProcStmtMatch;
class ITypeProcStmtRepeat;
class ITypeProcStmtRepeatWhile;
class ITypeProcStmtReturn;
class ITypeProcStmtScope;
class ITypeProcStmtVarDecl;
class ITypeProcStmtWhile;
class ITypeProcStmtYield;

class IVisitor : public virtual vsc::dm::IVisitor {
public:

	virtual ~IVisitor() { }

	virtual void visitDataTypeAction(IDataTypeAction *t) = 0;

	virtual void visitDataTypeActivity(IDataTypeActivity *t) = 0;

	virtual void visitDataTypeActivityBind(IDataTypeActivityBind *t) = 0;

	virtual void visitDataTypeActivityParallel(IDataTypeActivityParallel *t) = 0;

	virtual void visitDataTypeActivityReplicate(IDataTypeActivityReplicate *t) = 0;

	virtual void visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) = 0;

	virtual void visitDataTypeActivitySequence(IDataTypeActivitySequence *t) = 0;

	virtual void visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) = 0;

	virtual void visitDataTypeActivityTraverseType(IDataTypeActivityTraverseType *t) = 0;

	virtual void visitDataTypeAddrClaim(IDataTypeAddrClaim *t) = 0;

	virtual void visitDataTypeAddrClaimTransparent(IDataTypeAddrClaimTransparent *t) = 0;

	virtual void visitDataTypeAddrHandle(IDataTypeAddrHandle *t) = 0;

	virtual void visitDataTypeAddrSpaceC(IDataTypeAddrSpaceC *t) = 0;

	virtual void visitDataTypeAddrSpaceTransparentC(IDataTypeAddrSpaceTransparentC *t) = 0;

	virtual void visitDataTypeArlStruct(IDataTypeArlStruct *t) = 0;

	virtual void visitDataTypeComponent(IDataTypeComponent *t) = 0;

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) = 0;

	virtual void visitDataTypeFunction(IDataTypeFunction *t) = 0;

	virtual void visitDataTypeFunctionParamDecl(IDataTypeFunctionParamDecl *t) = 0;

	virtual void visitDataTypePackedStruct(IDataTypePackedStruct *t) = 0;

    virtual void visitDataTypePyObj(IDataTypePyObj *t) = 0;

	virtual void visitDataTypeRegGroup(IDataTypeRegGroup *t) = 0;

	virtual void visitDataTypeResource(IDataTypeResource *t) = 0;

	virtual void visitModelActivityBind(IModelActivityBind *a) = 0;

	virtual void visitModelActivityParallel(IModelActivityParallel *a) = 0;

	virtual void visitModelActivityReplicate(IModelActivityReplicate *a) = 0;

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) = 0;

	virtual void visitModelActivityScope(IModelActivityScope *a) = 0;

	virtual void visitModelActivitySequence(IModelActivitySequence *a) = 0;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) = 0;

	virtual void visitModelFieldAction(IModelFieldAction *f) = 0;

	virtual void visitModelFieldClaim(IModelFieldClaim *f) = 0;

	virtual void visitModelFieldComponent(IModelFieldComponent *f) = 0;

	virtual void visitModelFieldComponentRoot(IModelFieldComponentRoot *f) = 0;

	virtual void visitModelFieldExecutor(IModelFieldExecutor *f) = 0;

	virtual void visitModelFieldExecutorClaim(IModelFieldExecutorClaim *f) = 0;

	virtual void visitModelFieldInOut(IModelFieldInOut *f) = 0;

	virtual void visitModelFieldPool(IModelFieldPool *f) = 0;

	virtual void visitModelFieldRegGroup(IModelFieldRegGroup *f) = 0;

    virtual void visitTypeExprMethodCallContext(ITypeExprMethodCallContext *e) = 0;

    virtual void visitTypeExprMethodCallStatic(ITypeExprMethodCallStatic *e) = 0;

	virtual void visitTypeExec(ITypeExec *e) = 0;

	virtual void visitTypeExecProc(ITypeExecProc *e) = 0;

    virtual void visitTypeExprPyImportRef(ITypeExprPyImportRef *t) = 0;

    virtual void visitTypeExprPythonFieldRef(ITypeExprPythonFieldRef *t) = 0;

    virtual void visitTypeExprPythonMethodCall(ITypeExprPythonMethodCall *t) = 0;

    virtual void visitTypeExprPythonModuleRef(ITypeExprPythonModuleRef *t) = 0;

	virtual void visitTypeFieldActivity(ITypeFieldActivity *f) = 0;

	virtual void visitTypeFieldAddrClaim(ITypeFieldAddrClaim *f) = 0;

	virtual void visitTypeFieldAddrClaimTransparent(ITypeFieldAddrClaimTransparent *f) = 0;

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) = 0;

	virtual void visitTypeFieldExecutor(ITypeFieldExecutor *f) = 0;

	virtual void visitTypeFieldExecutorClaim(ITypeFieldExecutorClaim *f) = 0;

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) = 0;

	virtual void visitTypeFieldPool(ITypeFieldPool *f) = 0;

	virtual void visitTypeFieldReg(ITypeFieldReg *f) = 0;

	virtual void visitTypeFieldRegGroup(ITypeFieldRegGroup *f) = 0;

	virtual void visitTypeFieldRegGroupArr(ITypeFieldRegGroupArr *f) = 0;

	virtual void visitTypeProcStmt(ITypeProcStmt *s) = 0;

	virtual void visitTypeProcStmtAssign(ITypeProcStmtAssign *s) = 0;

	virtual void visitTypeProcStmtBreak(ITypeProcStmtBreak *s) = 0;

	virtual void visitTypeProcStmtContinue(ITypeProcStmtContinue *s) = 0;

	virtual void visitTypeProcStmtExpr(ITypeProcStmtExpr *s) = 0;

	virtual void visitTypeProcStmtForeach(ITypeProcStmtForeach *s) = 0;

	virtual void visitTypeProcStmtIfClause(ITypeProcStmtIfClause *s) = 0;

	virtual void visitTypeProcStmtIfElse(ITypeProcStmtIfElse *s) = 0;

	virtual void visitTypeProcStmtMatch(ITypeProcStmtMatch *s) = 0;

	virtual void visitTypeProcStmtRepeat(ITypeProcStmtRepeat *s) = 0;

	virtual void visitTypeProcStmtRepeatWhile(ITypeProcStmtRepeatWhile *s) = 0;

	virtual void visitTypeProcStmtReturn(ITypeProcStmtReturn *s) = 0;

	virtual void visitTypeProcStmtScope(ITypeProcStmtScope *s) = 0;

	virtual void visitTypeProcStmtVarDecl(ITypeProcStmtVarDecl *s) = 0;

	virtual void visitTypeProcStmtWhile(ITypeProcStmtWhile *s) = 0;

	virtual void visitTypeProcStmtYield(ITypeProcStmtYield *s) = 0;

};

}
}
}
