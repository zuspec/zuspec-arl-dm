/*
 * VisitorDelegator.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeFunction.h"
#include "arl/IDataTypeResource.h"
#include "arl/IDataTypeActivityReplicate.h"
#include "arl/IVisitor.h"
#include "arl/ITypeFieldExecutor.h"
#include "arl/ITypeFieldPool.h"
#include "arl/IModelFieldAction.h"
#include "arl/IModelFieldClaim.h"
#include "arl/IModelFieldExecutor.h"
#include "arl/IModelFieldInOut.h"
#include "arl/IModelActivityParallel.h"
#include "arl/IModelActivityReplicate.h"
#include "arl/IModelActivitySchedule.h"
#include "arl/IModelActivitySequence.h"
#include "arl/IModelActivityTraverse.h"
#include "vsc/impl/VisitorDelegator.h"

namespace arl {

class VisitorDelegator : public virtual arl::IVisitor, public vsc::VisitorDelegator {
public:
	VisitorDelegator(vsc::IVisitor *delegate) : vsc::VisitorDelegator(delegate) { }

	VisitorDelegator(arl::IVisitor *delegate) : vsc::VisitorDelegator(delegate) { }

	virtual void visitDataTypeAction(IDataTypeAction *i) override {
		delegate(&arl::IVisitor::visitDataTypeAction,
				&vsc::IVisitor::visitDataTypeStruct, i);
	}

	virtual void visitDataTypeActivityBind(IDataTypeActivityBind *t) override {
		delegate(&arl::IVisitor::visitDataTypeActivityBind, t);
	}

	virtual void visitDataTypeActivityParallel(IDataTypeActivityParallel *t) override {
		delegate(&arl::IVisitor::visitDataTypeActivityParallel,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivityReplicate(IDataTypeActivityReplicate *t) override {
		delegate(&arl::IVisitor::visitDataTypeActivityReplicate,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) override {
		delegate(&arl::IVisitor::visitDataTypeActivitySchedule,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivitySequence(IDataTypeActivitySequence *t) override {
		delegate(&arl::IVisitor::visitDataTypeActivitySequence,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) override {
		delegate(&arl::IVisitor::visitDataTypeActivityTraverse, t);
	}

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override {
		delegate(&arl::IVisitor::visitDataTypeComponent,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override {
		delegate(&arl::IVisitor::visitDataTypeFlowObj,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeFunction(IDataTypeFunction *t) override {
		delegate(&arl::IVisitor::visitDataTypeFunction, t);
	}

	virtual void visitDataTypeResource(IDataTypeResource *t) override {
		delegate(&arl::IVisitor::visitDataTypeResource,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitModelActivityBind(IModelActivityBind *a) override {
		delegate(&arl::IVisitor::visitModelActivityBind, a);
	}

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override {
		delegate(&arl::IVisitor::visitModelActivityParallel, a);
	}

	virtual void visitModelActivityReplicate(IModelActivityReplicate *a) override {
		delegate(&arl::IVisitor::visitModelActivityReplicate, a);
	}

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override {
		delegate(&arl::IVisitor::visitModelActivitySchedule, a);
	}

	virtual void visitModelActivityScope(IModelActivityScope *a) override {
		delegate(&arl::IVisitor::visitModelActivityScope, a);
	}

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override {
		delegate(&arl::IVisitor::visitModelActivitySequence, a);
	}


	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override {
		delegate(&arl::IVisitor::visitModelActivityTraverse, a);
	}

	virtual void visitModelFieldAction(IModelFieldAction *f) override {
		delegate(&arl::IVisitor::visitModelFieldAction,
				&vsc::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldClaim(IModelFieldClaim *f) override { 
		delegate(&arl::IVisitor::visitModelFieldClaim,
				&vsc::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldComponent(IModelFieldComponent *f) override {
		delegate(&arl::IVisitor::visitModelFieldComponent,
				&vsc::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldExecutor(IModelFieldExecutor *f) override {
		delegate(&arl::IVisitor::visitModelFieldExecutor,
				&vsc::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldExecutorClaim(IModelFieldExecutorClaim *f) override {
		delegate(&arl::IVisitor::visitModelFieldExecutorClaim,
				&vsc::IVisitor::visitModelFieldRef, f);
	}

	virtual void visitModelFieldInOut(IModelFieldInOut *f) override {
		delegate(&arl::IVisitor::visitModelFieldInOut,
				&vsc::IVisitor::visitModelFieldRef, f);
	}

	virtual void visitModelFieldPool(IModelFieldPool *f) override {
		delegate(&arl::IVisitor::visitModelFieldPool,
				&vsc::IVisitor::visitModelField, f);
	}

	virtual void visitTypeFieldActivity(ITypeFieldActivity *f) override {
		delegate(&arl::IVisitor::visitTypeFieldActivity,
				&vsc::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) override {
		delegate(&arl::IVisitor::visitTypeFieldClaim,
				&vsc::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldExecutor(ITypeFieldExecutor *f) override {
		delegate(&arl::IVisitor::visitTypeFieldExecutor,
				&vsc::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldExecutorClaim(ITypeFieldExecutorClaim *f) override {
		delegate(&arl::IVisitor::visitTypeFieldExecutorClaim,
				&vsc::IVisitor::visitTypeFieldRef, f);
	}

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) override {
		delegate(&arl::IVisitor::visitTypeFieldInOut,
				&vsc::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldPool(ITypeFieldPool *f) override {
		delegate(&arl::IVisitor::visitTypeFieldPool,
				&vsc::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeProcStmtAssign(ITypeProcStmtAssign *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtAssign, s);
	}

	virtual void visitTypeProcStmtBreak(ITypeProcStmtBreak *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtBreak, s);
	}

	virtual void visitTypeProcStmtContinue(ITypeProcStmtContinue *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtContinue, s);
	}

	virtual void visitTypeProcStmtForeach(ITypeProcStmtForeach *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtForeach, s);
	}

	virtual void visitTypeProcStmtIfElse(ITypeProcStmtIfElse *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtIfElse, s);
	}

	virtual void visitTypeProcStmtMatch(ITypeProcStmtMatch *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtMatch, s);
	}

	virtual void visitTypeProcStmtRepeat(ITypeProcStmtRepeat *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtRepeat, s);
	}

	virtual void visitTypeProcStmtRepeatWhile(ITypeProcStmtRepeatWhile *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtRepeatWhile, s);
	}

	virtual void visitTypeProcStmtReturn(ITypeProcStmtReturn *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtReturn, s);
	}

	virtual void visitTypeProcStmtScope(ITypeProcStmtScope *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtScope, s);
	}

	virtual void visitTypeProcStmtVarDecl(ITypeProcStmtVarDecl *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtVarDecl, s);
	}

	virtual void visitTypeProcStmtWhile(ITypeProcStmtWhile *s) override {
		delegate(&arl::IVisitor::visitTypeProcStmtWhile, s);
	}

private:

	template <class T1, class T2> void delegate(
			void (arl::IVisitor::*f1)(T1 *),
			void (vsc::IVisitor::*f2)(T2 *),
			T1 *v) {
		if (delegate()) {
			((*delegate()).*f1)(v);
		} else if (m_delegate->cascade()) {
			((*vsc::VisitorDelegator::delegate()).*f2)(v);
		}
	}

	template <class T1> void delegate(
			void (arl::IVisitor::*f1)(T1 *),
			T1 *v) {
		if (delegate()) {
			((*delegate()).*f1)(v);
		} else {
			// TODO: fatal
		}
	}

	arl::IVisitor *delegate() const { return dynamic_cast<arl::IVisitor *>(m_delegate); }
};

}
