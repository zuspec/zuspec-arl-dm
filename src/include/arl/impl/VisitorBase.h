/*
 * VisitorBase.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/impl/VisitorBase.h"

#include "arl/IDataTypeAction.h"
#include "arl/IDataTypeComponent.h"
#include "arl/IDataTypeFlowObj.h"
#include "arl/IVisitor.h"
#include "arl/ITypeActivityStmtTraverseType.h"

namespace arl {

class VisitorBase : public virtual arl::IVisitor, public vsc::VisitorBase {
public:

	VisitorBase(vsc::IVisitor *this_p=0) : vsc::VisitorBase(this_p) { }

	VisitorBase(arl::IVisitor *this_p) : vsc::VisitorBase(this_p) { }

	virtual ~VisitorBase() { }

	virtual void visitDataTypeAction(IDataTypeAction *i) override {
		vsc::VisitorBase::visitDataTypeStruct(i);
	}

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override {
		vsc::VisitorBase::visitDataTypeStruct(t);
	}

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override {
		vsc::VisitorBase::visitDataTypeStruct(t);
	}

	virtual void visitTypeActivityStmtTraverseType(ITypeActivityStmtTraverseType *s) override {
		s->getType()->accept(this);
	}
};

}
