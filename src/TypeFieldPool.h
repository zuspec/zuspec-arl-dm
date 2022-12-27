/*
 * TypeFieldPool.h
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/ITypeFieldPool.h"
#include "TypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class TypeFieldPool : public virtual ITypeFieldPool, public TypeField {
public:
	TypeFieldPool(
			IContext					*ctxt,
			const std::string			&name,
			vsc::dm::IDataType				*type,
			bool						own,
			vsc::dm::TypeFieldAttr			attr,
			int32_t						decl_size);

	virtual ~TypeFieldPool();

	virtual int32_t getDeclSize() override { return -1; }

	virtual vsc::dm::IModelField *mkModelField(
		vsc::dm::IModelBuildContext 			*ctxt) override;

	virtual void accept(vsc::dm::IVisitor *v) override;

private:
	vsc::dm::IDataType						*m_pool_t;
	vsc::dm::IDataTypeUP					m_pool_t_u;
	vsc::dm::ITypeField						*m_decl_size;

};

}
}
}

