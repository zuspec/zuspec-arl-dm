/*
 * VisitorBase.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/impl/VisitorBase.h"

#include "arl/IDataTypeAction.h"
#include "arl/IDataTypeActivitySchedule.h"
#include "arl/IDataTypeActivitySequence.h"
#include "arl/IDataTypeActivityTraverse.h"
#include "arl/IDataTypeComponent.h"
#include "arl/IDataTypeFlowObj.h"
#include "arl/IModelFieldRootComponent.h"
#include "arl/IVisitor.h"
#include "arl/ITypeActivitySequence.h"
#include "arl/ITypeActivityStmtTraverseType.h"
#include "arl/ITypeFieldClaim.h"
#include "arl/ITypeFieldInOut.h"
#include "arl/ITypeFieldPool.h"

namespace arl {

class VisitorBase : public virtual arl::IVisitor, public vsc::VisitorBase {
public:

	VisitorBase(vsc::IVisitor *this_p=0) : vsc::VisitorBase(this_p) { }

	VisitorBase(arl::IVisitor *this_p) : vsc::VisitorBase(this_p) { }

	virtual ~VisitorBase() { }

	virtual void visitDataTypeAction(IDataTypeAction *i) override {
		vsc::VisitorBase::visitDataTypeStruct(i);
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

	virtual void visitModelFieldRootComponent(IModelFieldRootComponent *f) override {
		vsc::VisitorBase::visitModelField(f);
	}

	virtual void visitTypeActivitySequence(ITypeActivitySequence *s) override {
		for (std::vector<ITypeActivityStmtUP>::const_iterator
				it=s->getStmts().begin();
				it!=s->getStmts().end(); it++) {
			it->get()->accept(m_this);
		}
	}

	virtual void visitTypeActivityStmtTraverseType(ITypeActivityStmtTraverseType *s) override {
		s->getType()->accept(this);
	}

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) override {
		vsc::VisitorBase::visitTypeField(f);
	}

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) override {
		vsc::VisitorBase::visitTypeField(f);
	}

	virtual void visitTypeFieldPool(ITypeFieldPool *f) override {
		vsc::VisitorBase::visitTypeField(f);
	}
};

}
