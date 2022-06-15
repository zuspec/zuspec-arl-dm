/*
 * ITypeActivityStmtTraverseType.h
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeAction.h"
#include "sav/ITypeActivityStmtTraverse.h"

namespace arl {

class ITypeActivityStmtTraverseType : public virtual ITypeActivityStmtTraverse {
public:

	virtual ~ITypeActivityStmtTraverseType() { }

	virtual IDataTypeAction *getType() = 0;

};

}

