/*
 * TypeFieldClaim.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */
#pragma once
#include "zsp/arl/dm/ITypeFieldClaim.h"
#include "TypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class TypeFieldClaim : public virtual ITypeFieldClaim, public TypeField {
public:
	TypeFieldClaim(
			const std::string			&name,
			vsc::dm::IDataType			*type,
			bool						is_lock);

	virtual ~TypeFieldClaim();

	virtual bool isLock() const override { return m_is_lock; }

	virtual vsc::dm::IModelField *mkModelField(
		vsc::dm::IModelBuildContext 	*ctxt,
        const vsc::dm::ValRef           &val) override;

	virtual void accept(vsc::dm::IVisitor *v) override;

private:
	bool								m_is_lock;
};

}
}
}

