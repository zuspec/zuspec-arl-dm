/*
 * TypeActivityStmtTraverse.h
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#pragma once
#include "include/arl/sav/ITypeActivityStmtTraverse.h"

namespace arl {

class TypeActivityStmtTraverse : public virtual ITypeActivityStmtTraverse {
public:
	TypeActivityStmtTraverse(vsc::ITypeConstraint *constraints);

	virtual ~TypeActivityStmtTraverse();

	virtual vsc::ITypeConstraint *getConstraint() override {
		return m_constraint.get();
	}

private:
	vsc::ITypeConstraintUP			m_constraint;
};

} /* namespace arl */

