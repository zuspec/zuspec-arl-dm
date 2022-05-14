/*
 * TypeFieldPool.h
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/ITypeFieldPool.h"
#include "TypeField.h"

namespace arl {

class TypeFieldPool : public virtual ITypeFieldPool, public TypeField {
public:
	TypeFieldPool(
			const std::string			&name,
			vsc::IDataType				*type,
			vsc::TypeFieldAttr			attr,
			int32_t						decl_size);

	virtual ~TypeFieldPool();

	virtual int32_t getDeclSize() override { return m_decl_size; }

	virtual void accept(vsc::IVisitor *v) override;

private:
	int32_t								m_decl_size;

};

} /* namespace arl */

