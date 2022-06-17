/*
 * DataTypeActivityTraverse.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */
#pragma once
#include "arl/IDataTypeActivityTraverse.h"
#include "vsc/ITypeConstraint.h"


namespace arl {

class DataTypeActivityTraverse : public IDataTypeActivityTraverse {
public:
	DataTypeActivityTraverse(
			vsc::ITypeExprFieldRef		*target,
			vsc::ITypeConstraint		*with_c);

	virtual ~DataTypeActivityTraverse();

	virtual vsc::ITypeExprFieldRef *getTarget() const override {
		return m_target.get();
	}

	virtual vsc::ITypeConstraint *getWithC() const override {
		return m_with_c.get();
	}

	virtual void setWithC(vsc::ITypeConstraint *c) override {
		m_with_c = vsc::ITypeConstraintUP(c);
	}

	virtual void accept(vsc::IVisitor *v) override;

private:
	vsc::ITypeExprFieldRefUP				m_target;
	vsc::ITypeConstraintUP					m_with_c;
};

} /* namespace arl */

