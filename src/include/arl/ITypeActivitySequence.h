/*
 * ITypeActivitySequence.h
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/ITypeActivityStmt.h"

namespace arl {

class ITypeActivitySequence;
using ITypeActivitySequenceUP=std::unique_ptr<ITypeActivitySequence>;
class ITypeActivitySequence : public ITypeActivityStmt {
public:

	virtual ~ITypeActivitySequence() { }

	virtual const std::vector<ITypeActivityStmtUP> &getStmts() const = 0;

	virtual void addStmt(ITypeActivityStmt *s) = 0;

};

}
