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
class IDataTypeFlowObj;

class IVisitor : public vsc::IVisitor {
public:

	virtual ~IVisitor() { }

	virtual void visitDataTypeAction(IDataTypeAction *i) = 0;

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) = 0;

};

}
