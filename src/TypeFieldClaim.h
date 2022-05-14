/*
 * TypeFieldClaim.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */
#pragma once
#include "arl/ITypeFieldClaim.h"
#include "TypeField.h"

namespace arl {

class TypeFieldClaim : public virtual ITypeFieldClaim, public TypeField {
public:
	TypeFieldClaim(
			const std::string			&name,
			vsc::IDataType				*type,
			bool						is_lock);

	virtual ~TypeFieldClaim();

	virtual bool isLock() const override { return m_is_lock; }

	virtual void accept(vsc::IVisitor *v) override;

private:
	bool								m_is_lock;
};

} /* namespace arl */

