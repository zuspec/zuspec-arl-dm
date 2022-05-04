/*
 * ITypeActivityScope.h
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <vector>
#include "arl/ITypeActivityStmt.h"

namespace arl {

class ITypeActivityScope;
using ITypeActivityScopeUP=std::unique_ptr<ITypeActivityScope>;
class ITypeActivityScope : public virtual ITypeActivityStmt {
public:

	virtual ~ITypeActivityScope() { }

	virtual const std::vector<ITypeActivityStmtUP> &getStmts() const = 0;

	virtual void addStmt(ITypeActivityStmt *s) = 0;

};

}
