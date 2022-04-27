/*
 * IVisitor.h
 *
 *  Created on: Apr 2, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IVisitor.h"

namespace arl {

class IDataTypeAction;
class IDataTypeComponent;
class IDataTypeFlowObj;

class IVisitor : public virtual vsc::IVisitor {
public:

	virtual ~IVisitor() { }

	virtual void visitDataTypeAction(IDataTypeAction *t) = 0;

	virtual void visitDataTypeComponent(IDataTypeComponent *t) = 0;

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) = 0;

};

}
