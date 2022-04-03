/*
 * IVisitor.h
 *
 *  Created on: Apr 2, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IVisitor.h"

namespace arl {

class ITypeAction;

class IVisitor : public vsc::IVisitor {
public:

	virtual ~IVisitor() { }

	virtual void visitTypeAction(ITypeAction *i) = 0;

};

}
