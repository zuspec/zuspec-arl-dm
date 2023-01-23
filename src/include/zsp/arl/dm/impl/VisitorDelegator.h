/*
 * VisitorDelegator.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeFunction.h"
#include "zsp/arl/dm/IDataTypeResource.h"
#include "zsp/arl/dm/IDataTypeActivityReplicate.h"
#include "zsp/arl/dm/IVisitor.h"
#include "zsp/arl/dm/ITypeFieldExecutor.h"
#include "zsp/arl/dm/ITypeFieldPool.h"
#include "zsp/arl/dm/IModelFieldAction.h"
#include "zsp/arl/dm/IModelFieldClaim.h"
#include "zsp/arl/dm/IModelFieldComponent.h"
#include "zsp/arl/dm/IModelFieldComponentRoot.h"
#include "zsp/arl/dm/IModelFieldExecutor.h"
#include "zsp/arl/dm/IModelFieldInOut.h"
#include "zsp/arl/dm/IModelActivityParallel.h"
#include "zsp/arl/dm/IModelActivityReplicate.h"
#include "zsp/arl/dm/IModelActivitySchedule.h"
#include "zsp/arl/dm/IModelActivitySequence.h"
#include "zsp/arl/dm/IModelActivityTraverse.h"
#include "zsp/arl/dm/ITypeExprMethodCallContext.h"
#include "zsp/arl/dm/ITypeExprMethodCallStatic.h"
#include "vsc/dm/impl/VisitorDelegator.h"

namespace zsp {
namespace arl {
namespace dm {


class VisitorDelegator : public virtual arl::dm::IVisitor, public vsc::dm::VisitorDelegator {
public:
	VisitorDelegator(vsc::dm::IVisitor *delegate) : vsc::dm::VisitorDelegator(delegate) { }

	VisitorDelegator(arl::dm::IVisitor *delegate) : vsc::dm::VisitorDelegator(delegate) { }

	virtual void visitDataTypeAction(IDataTypeAction *i) override {
		delegate(&arl::dm::IVisitor::visitDataTypeAction,
				&vsc::dm::IVisitor::visitDataTypeStruct, i);
	}

	virtual void visitDataTypeActivityBind(IDataTypeActivityBind *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeActivityBind, t);
	}

	virtual void visitDataTypeActivityParallel(IDataTypeActivityParallel *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeActivityParallel,
				&vsc::dm::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivityReplicate(IDataTypeActivityReplicate *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeActivityReplicate,
				&vsc::dm::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeActivitySchedule,
				&vsc::dm::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivitySequence(IDataTypeActivitySequence *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeActivitySequence,
				&vsc::dm::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeActivityTraverse, t);
	}

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeComponent,
				&vsc::dm::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeFlowObj,
				&vsc::dm::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeFunction(IDataTypeFunction *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeFunction, t);
	}

	virtual void visitDataTypeFunctionParamDecl(IDataTypeFunctionParamDecl *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeFunctionParamDecl, t);
	}

	virtual void visitDataTypeResource(IDataTypeResource *t) override {
		delegate(&arl::dm::IVisitor::visitDataTypeResource,
				&vsc::dm::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitModelActivityBind(IModelActivityBind *a) override {
		delegate(&arl::dm::IVisitor::visitModelActivityBind, a);
	}

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override {
		delegate(&arl::dm::IVisitor::visitModelActivityParallel, a);
	}

	virtual void visitModelActivityReplicate(IModelActivityReplicate *a) override {
		delegate(&arl::dm::IVisitor::visitModelActivityReplicate, a);
	}

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override {
		delegate(&arl::dm::IVisitor::visitModelActivitySchedule, a);
	}

	virtual void visitModelActivityScope(IModelActivityScope *a) override {
		delegate(&arl::dm::IVisitor::visitModelActivityScope, a);
	}

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override {
		delegate(&arl::dm::IVisitor::visitModelActivitySequence, a);
	}


	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override {
		delegate(&arl::dm::IVisitor::visitModelActivityTraverse, a);
	}

	virtual void visitModelFieldAction(IModelFieldAction *f) override {
		delegate(&arl::dm::IVisitor::visitModelFieldAction,
				&vsc::dm::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldClaim(IModelFieldClaim *f) override { 
		delegate(&arl::dm::IVisitor::visitModelFieldClaim,
				&vsc::dm::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldComponent(IModelFieldComponent *f) override {
		delegate(&arl::dm::IVisitor::visitModelFieldComponent,
				&vsc::dm::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldComponentRoot(IModelFieldComponentRoot *f) override {
		delegate(&arl::dm::IVisitor::visitModelFieldComponentRoot,
				&vsc::dm::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldExecutor(IModelFieldExecutor *f) override {
		delegate(&arl::dm::IVisitor::visitModelFieldExecutor,
				&vsc::dm::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldExecutorClaim(IModelFieldExecutorClaim *f) override {
		delegate(&arl::dm::IVisitor::visitModelFieldExecutorClaim,
				&vsc::dm::IVisitor::visitModelFieldRef, f);
	}

	virtual void visitModelFieldInOut(IModelFieldInOut *f) override {
		delegate(&arl::dm::IVisitor::visitModelFieldInOut,
				&vsc::dm::IVisitor::visitModelFieldRef, f);
	}

	virtual void visitModelFieldPool(IModelFieldPool *f) override {
		delegate(&arl::dm::IVisitor::visitModelFieldPool,
				&vsc::dm::IVisitor::visitModelField, f);
	}

    virtual void visitTypeExprMethodCallContext(ITypeExprMethodCallContext *e) override {
        delegate(&arl::dm::IVisitor::visitTypeExprMethodCallContext, e);
    }

    virtual void visitTypeExprMethodCallStatic(ITypeExprMethodCallStatic *e) override {
        delegate(&arl::dm::IVisitor::visitTypeExprMethodCallStatic, e);
    }

	virtual void visitTypeExec(ITypeExec *e) override {
        delegate(&arl::dm::IVisitor::visitTypeExec, e);
    }

	virtual void visitTypeExecProc(ITypeExecProc *e) override {
        delegate(&arl::dm::IVisitor::visitTypeExecProc, e);
    }

	virtual void visitTypeFieldActivity(ITypeFieldActivity *f) override {
		delegate(&arl::dm::IVisitor::visitTypeFieldActivity,
				&vsc::dm::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) override {
		delegate(&arl::dm::IVisitor::visitTypeFieldClaim,
				&vsc::dm::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldExecutor(ITypeFieldExecutor *f) override {
		delegate(&arl::dm::IVisitor::visitTypeFieldExecutor,
				&vsc::dm::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldExecutorClaim(ITypeFieldExecutorClaim *f) override {
		delegate(&arl::dm::IVisitor::visitTypeFieldExecutorClaim,
				&vsc::dm::IVisitor::visitTypeFieldRef, f);
	}

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) override {
		delegate(&arl::dm::IVisitor::visitTypeFieldInOut,
				&vsc::dm::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldPool(ITypeFieldPool *f) override {
		delegate(&arl::dm::IVisitor::visitTypeFieldPool,
				&vsc::dm::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeProcStmtAssign(ITypeProcStmtAssign *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtAssign, s);
	}

	virtual void visitTypeProcStmtBreak(ITypeProcStmtBreak *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtBreak, s);
	}

	virtual void visitTypeProcStmtContinue(ITypeProcStmtContinue *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtContinue, s);
	}

	virtual void visitTypeProcStmtExpr(ITypeProcStmtExpr *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtExpr, s);
	}

	virtual void visitTypeProcStmtForeach(ITypeProcStmtForeach *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtForeach, s);
	}

	virtual void visitTypeProcStmtIfElse(ITypeProcStmtIfElse *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtIfElse, s);
	}

	virtual void visitTypeProcStmtMatch(ITypeProcStmtMatch *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtMatch, s);
	}

	virtual void visitTypeProcStmtRepeat(ITypeProcStmtRepeat *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtRepeat, s);
	}

	virtual void visitTypeProcStmtRepeatWhile(ITypeProcStmtRepeatWhile *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtRepeatWhile, s);
	}

	virtual void visitTypeProcStmtReturn(ITypeProcStmtReturn *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtReturn, s);
	}

	virtual void visitTypeProcStmtScope(ITypeProcStmtScope *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtScope, s);
	}

	virtual void visitTypeProcStmtVarDecl(ITypeProcStmtVarDecl *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtVarDecl, s);
	}

	virtual void visitTypeProcStmtWhile(ITypeProcStmtWhile *s) override {
		delegate(&arl::dm::IVisitor::visitTypeProcStmtWhile, s);
	}

private:

	template <class T1, class T2> void delegate(
			void (arl::dm::IVisitor::*f1)(T1 *),
			void (vsc::dm::IVisitor::*f2)(T2 *),
			T1 *v) {
		if (delegate()) {
			((*delegate()).*f1)(v);
		} else if (m_delegate->cascade()) {
			((*vsc::dm::VisitorDelegator::delegate()).*f2)(v);
		}
	}

	template <class T1> void delegate(
			void (arl::dm::IVisitor::*f1)(T1 *),
			T1 *v) {
		if (delegate()) {
			((*delegate()).*f1)(v);
		} else {
			// TODO: fatal
		}
	}

	arl::dm::IVisitor *delegate() const { return dynamic_cast<arl::dm::IVisitor *>(m_delegate); }
};

}
}
}
