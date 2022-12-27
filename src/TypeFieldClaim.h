/*
 * TypeFieldClaim.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */
#pragma once
#include "arl/ITypeFieldClaim.h"
#include "TypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class TypeFieldClaim : public virtual ITypeFieldClaim, public TypeField {
public:
	TypeFieldClaim(
			const std::string			&name,
			vsc::IDataType				*type,
			bool						is_lock);

	virtual ~TypeFieldClaim();

	virtual bool isLock() const override { return m_is_lock; }

	virtual vsc::IModelField *mkModelField(
		vsc::IModelBuildContext 			*ctxt) override;

	virtual void accept(vsc::IVisitor *v) override;

private:
	bool								m_is_lock;
};

}
}
}

