/*
 * VisitorBase.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeAction.h"
#include "arl/IVisitor.h"
#include "vsc/VisitorBase.h"

namespace arl {

class VisitorBase : public vsc::VisitorBase, public IVisitor {
public:

	virtual ~VisitorBase() { }

	virtual void visitDataTypeAction(IDataTypeAction *i) override {
		vsc::VisitorBase::visitDataTypeStruct(i);
	}

};

}
