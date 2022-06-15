/*
 * ITypeActivityStmtTraverse.h
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#pragma once
#include "sav/ITypeActivityStmt.h"
#include "vsc/ITypeConstraint.h"

namespace arl {

class ITypeActivityStmtTraverse : public ITypeActivityStmt {
public:

	virtual ~ITypeActivityStmtTraverse() { }

	virtual vsc::ITypeConstraint *getConstraint() = 0;

};

}
