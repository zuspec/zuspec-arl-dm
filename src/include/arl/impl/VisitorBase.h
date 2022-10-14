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
#include "arl/IDataTypeResource.h"
#include "arl/IModelActivityParallel.h"
#include "arl/IModelActivitySchedule.h"
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
		for (std::vector<IModelActivityScope *>::const_iterator
				it=f->activities().begin();
				it!=f->activities().end(); it++) {
			(*it)->accept(m_this);
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
};

}
