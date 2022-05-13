/*
 * TypeFieldPool.h
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/ITypeFieldPool.h"

namespace arl {

class TypeFieldPool : public ITypeFieldPool {
public:
	TypeFieldPool(
			const std::string			&name,
			vsc::IDataType				*type,
			vsc::TypeFieldAttr			attr,
			int32_t						decl_size);

	virtual ~TypeFieldPool();

	virtual vsc::IDataTypeStruct *getParent() override {
		return m_parent;
	}

	virtual void setParent(vsc::IDataTypeStruct *p) override {
		m_parent = p;
	}

	virtual const std::string &name() const { return m_name; }

	virtual vsc::IDataType *getDataType() const override {
		return m_type;
	}

	virtual void setDataType(vsc::IDataType *t) override {
		m_type = t;
	}

	virtual vsc::TypeFieldAttr getAttr() const override {
		return m_attr;
	}

	virtual int32_t getDeclSize() override { return m_decl_size; }

	virtual void accept(vsc::IVisitor *v) override;

private:
	vsc::IDataTypeStruct				*m_parent;
	std::string							m_name;
	vsc::IDataType						*m_type;
	vsc::TypeFieldAttr					m_attr;
	int32_t								m_decl_size;

};

} /* namespace arl */

