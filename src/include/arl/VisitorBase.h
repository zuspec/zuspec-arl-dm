/*
 * VisitorBase.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeAction.h"
#include "arl/IDataTypeComponent.h"
#include "arl/IDataTypeFlowObj.h"
#include "arl/IVisitor.h"
#include "vsc/VisitorBase.h"

namespace arl {

class VisitorBase : public virtual IVisitor, public vsc::VisitorBase {
public:

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

};

}
