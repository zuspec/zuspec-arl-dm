/*
 * TypeActivityScope.h
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/ITypeActivityScope.h"

namespace arl {

class TypeActivityScope : public ITypeActivityScope {
public:
	TypeActivityScope();

	virtual ~TypeActivityScope();

	virtual const std::vector<ITypeActivityStmtUP> &getStmts() const override {
		return m_stmts;
	}

	virtual void addStmt(ITypeActivityStmt *s) override {
		m_stmts.push_back(ITypeActivityStmtUP(s));
	}

protected:
	std::vector<ITypeActivityStmtUP>		m_stmts;

};

} /* namespace arl */

