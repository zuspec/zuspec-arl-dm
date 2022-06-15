/*
 * TypeActivityStmtTraverseType.h
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#pragma once
#include "include/arl/sav/ITypeActivityStmtTraverseType.h"
#include "sav/TypeActivityStmtTraverse.h"

namespace arl {

class TypeActivityStmtTraverseType : public virtual ITypeActivityStmtTraverseType, public TypeActivityStmtTraverse {
public:
	TypeActivityStmtTraverseType(
			IDataTypeAction					*action_t,
			vsc::ITypeConstraint			*constraint
			);

	virtual ~TypeActivityStmtTraverseType();

	virtual IDataTypeAction *getType() { return m_action_t.get(); }

	virtual void accept(vsc::IVisitor *v) override;

private:
	IDataTypeActionUP						m_action_t;

};

} /* namespace arl */

