/*
 * VisitorBase.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/impl/VisitorBase.h"

#include "arl/IDataTypeAction.h"
#include "arl/IDataTypeActivityParallel.h"
#include "arl/IDataTypeActivitySchedule.h"
#include "arl/IDataTypeActivitySequence.h"
#include "arl/IDataTypeActivityTraverse.h"
#include "arl/IDataTypeComponent.h"
#include "arl/IDataTypeFlowObj.h"
#include "arl/IDataTypeFunction.h"
#include "arl/IDataTypeResource.h"
#include "arl/IModelActivityParallel.h"
#include "arl/IModelActivitySchedule.h"
#include "arl/IModelActivityScope.h"
#include "arl/IModelActivitySequence.h"
#include "arl/IModelActivityTraverse.h"
#include "arl/IModelFieldAction.h"
#include "arl/IModelFieldComponent.h"
#include "arl/IModelFieldExecutor.h"
#include "arl/IModelFieldExecutorClaim.h"
#include "arl/IModelFieldPool.h"
#include "arl/IVisitor.h"
#include "arl/ITypeFieldActivity.h"
#include "arl/ITypeFieldClaim.h"
#include "arl/ITypeFieldExecutor.h"
#include "arl/ITypeFieldExecutorClaim.h"
#include "arl/ITypeFieldInOut.h"
#include "arl/ITypeFieldPool.h"
#include "arl/ITypeProcStmtAssign.h"
#include "arl/ITypeProcStmtBreak.h"
#include "arl/ITypeProcStmtContinue.h"
#include "arl/ITypeProcStmtForeach.h"
#include "arl/ITypeProcStmtIfElse.h"
#include "arl/ITypeProcStmtMatch.h"
#include "arl/ITypeProcStmtRepeat.h"
#include "arl/ITypeProcStmtRepeatWhile.h"
#include "arl/ITypeProcStmtReturn.h"
#include "arl/ITypeProcStmtScope.h"
#include "arl/ITypeProcStmtVarDecl.h"
#include "arl/ITypeProcStmtWhile.h"

namespace arl {

class VisitorBase : public virtual arl::IVisitor, public vsc::VisitorBase {
public:

	VisitorBase(bool cascade=true, vsc::IVisitor *this_p=0) : vsc::VisitorBase(cascade, this_p) { }

	VisitorBase(arl::IVisitor *this_p) : vsc::VisitorBase(this_p) { }

	virtual ~VisitorBase() { }

	virtual void visitDataTypeAction(IDataTypeAction *i) override {
		vsc::VisitorBase::visitDataTypeStruct(i);
		for (std::vector<ITypeFieldActivity *>::const_iterator
				it=i->activities().begin();
				it!=i->activities().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitDataTypeActivityParallel(IDataTypeActivityParallel *t) override {
		vsc::VisitorBase::visitDataTypeStruct(t);
	}

	virtual void visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) override {
		vsc::VisitorBase::visitDataTypeStruct(t);
	}

	virtual void visitDataTypeActivitySequence(IDataTypeActivitySequence *t) override {
		vsc::VisitorBase::visitDataTypeStruct(t);
	}

	virtual void visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) override { }

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override {
		vsc::VisitorBase::visitDataTypeStruct(t);
	}

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override {
		vsc::VisitorBase::visitDataTypeStruct(t);
	}

	virtual void visitDataTypeFunction(IDataTypeFunction *t) override {

	}

	virtual void visitDataTypeResource(IDataTypeResource *t) override {
		visitDataTypeFlowObj(t);
	}

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override {
		for (std::vector<IModelActivity *>::const_iterator
				it=a->branches().begin();
				it!=a->branches().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override {
		for (std::vector<IModelActivity *>::const_iterator
				it=a->activities().begin();
				it!=a->activities().end(); it++) {
			(*it)->accept(m_this);
		}
	}
	
	virtual void visitModelActivityScope(IModelActivityScope *a) override {
		for (std::vector<IModelActivity *>::const_iterator
				it=a->activities().begin();
				it!=a->activities().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override {
		for (std::vector<IModelActivity *>::const_iterator
				it=a->activities().begin();
				it!=a->activities().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override {
		a->getTarget()->accept(m_this);
		if (a->getWithC()) {
			a->getWithC()->accept(m_this);
		}
	}

	virtual void visitModelFieldAction(IModelFieldAction *f) override {
		vsc::VisitorBase::visitModelField(f);
		if (f->getActivity()) {
			f->getActivity()->accept(m_this);
		}
	}

	virtual void visitModelFieldComponent(IModelFieldComponent *f) override {
		vsc::VisitorBase::visitModelField(f);
	}

	virtual void visitModelFieldExecutor(IModelFieldExecutor *f) override {
		vsc::VisitorBase::visitModelField(f);
	}

	virtual void visitModelFieldExecutorClaim(IModelFieldExecutorClaim *f) override {
		vsc::VisitorBase::visitModelFieldRef(f);
	}

	virtual void visitModelFieldPool(IModelFieldPool *f) override {
		vsc::VisitorBase::visitModelField(f);
	}

	virtual void visitTypeFieldActivity(ITypeFieldActivity *f) override {
		vsc::VisitorBase::visitTypeField(f);
	}

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) override {
		vsc::VisitorBase::visitTypeFieldRef(f);
	}

	virtual void visitTypeFieldExecutor(ITypeFieldExecutor *f) override {
		vsc::VisitorBase::visitTypeField(f);
	}

	virtual void visitTypeFieldExecutorClaim(ITypeFieldExecutorClaim *f) override {
		vsc::VisitorBase::visitTypeFieldRef(f);
	}

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) override {
		vsc::VisitorBase::visitTypeFieldRef(f);
	}

	virtual void visitTypeFieldPool(ITypeFieldPool *f) override {
		vsc::VisitorBase::visitTypeField(f);
	}

	virtual void visitTypeProcStmtAssign(ITypeProcStmtAssign *s) override {
		s->getLhs()->accept(m_this);
		s->getRhs()->accept(m_this);
	}

	virtual void visitTypeProcStmtBreak(ITypeProcStmtBreak *s) override {

	}

	virtual void visitTypeProcStmtContinue(ITypeProcStmtContinue *s) override {

	}

	virtual void visitTypeProcStmtForeach(ITypeProcStmtForeach *s) override {

	}

	virtual void visitTypeProcStmtIfElse(ITypeProcStmtIfElse *s) override {
		s->getCond()->accept(m_this);
		s->getTrue()->accept(m_this);
		if (s->getFalse()) {
			s->getFalse()->accept(m_this);
		}
	}

	virtual void visitTypeProcStmtMatch(ITypeProcStmtMatch *s) override {
		s->getCond()->accept(m_this);
	}

	virtual void visitTypeProcStmtRepeat(ITypeProcStmtRepeat *s) override {
		s->getExpr()->accept(m_this);
		s->getBody()->accept(m_this);
	}

	virtual void visitTypeProcStmtRepeatWhile(ITypeProcStmtRepeatWhile *s) override {
		s->getExpr()->accept(m_this);
		s->getBody()->accept(m_this);
	}

	virtual void visitTypeProcStmtReturn(ITypeProcStmtReturn *s) override {
		if (s->getExpr()) {
			s->getExpr()->accept(m_this);
		}
	}

	virtual void visitTypeProcStmtScope(ITypeProcStmtScope *s) override {
		for (std::vector<ITypeProcStmtUP>::const_iterator
			it=s->getStatements().begin();
			it!=s->getStatements().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitTypeProcStmtVarDecl(ITypeProcStmtVarDecl *s) override {
		s->getDataType()->accept(m_this);
		if (s->getInit()) {
			s->getInit()->accept(m_this);
		}
	}

	virtual void visitTypeProcStmtWhile(ITypeProcStmtWhile *s) override {
		s->getExpr()->accept(m_this);
		s->getBody()->accept(m_this);
	}
};

}
