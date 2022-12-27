/*
 * TypeFieldPool.h
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "arl/ITypeFieldPool.h"
#include "TypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class TypeFieldPool : public virtual ITypeFieldPool, public TypeField {
public:
	TypeFieldPool(
			IContext					*ctxt,
			const std::string			&name,
			vsc::IDataType				*type,
			bool						own,
			vsc::TypeFieldAttr			attr,
			int32_t						decl_size);

	virtual ~TypeFieldPool();

	virtual int32_t getDeclSize() override { return -1; }

	virtual vsc::IModelField *mkModelField(
		vsc::IModelBuildContext 			*ctxt) override;

	virtual void accept(vsc::IVisitor *v) override;

private:
	vsc::IDataType						*m_pool_t;
	vsc::IDataTypeUP					m_pool_t_u;
	vsc::ITypeField						*m_decl_size;

};

}
}
}

