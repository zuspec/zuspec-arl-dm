/*
 * TypeActivitySequence.h
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/ITypeActivitySequence.h"

namespace arl {

class TypeActivitySequence : public ITypeActivitySequence {
public:
	TypeActivitySequence();

	virtual ~TypeActivitySequence();

	virtual const std::vector<ITypeActivityStmtUP> &getStmts() const override {
		return m_stmts;
	}

	virtual void addStmt(ITypeActivityStmt *s) override {
		m_stmts.push_back(ITypeActivityStmtUP(s));
	}

	virtual void accept(vsc::IVisitor *v) override;

private:
	std::vector<ITypeActivityStmtUP>			m_stmts;
};

} /* namespace arl */

