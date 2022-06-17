/*
 * TypeField.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeField.h"

namespace arl {

class TypeField : public virtual vsc::ITypeField {
public:
	TypeField(
			const std::string			&name,
			vsc::IDataType				*type,
			vsc::TypeFieldAttr			attr);

	virtual ~TypeField();

	virtual vsc::IDataTypeStruct *getParent() override {
		return m_parent;
	}

	virtual void setParent(vsc::IDataTypeStruct *p) override {
		m_parent = p;
	}

	virtual int32_t getIndex() override { return m_idx; }

	virtual void setIndex(int32_t idx) override { m_idx = idx; }

	virtual const std::string &name() const { return m_name; }

	virtual vsc::IDataType *getDataType() const override {
		return m_type;
	}

	virtual void setDataType(vsc::IDataType *t) override {
		m_type = t;
	}

	virtual vsc::ITypeField *getField(int32_t idx) override;

	virtual vsc::TypeFieldAttr getAttr() const override {
		return m_attr;
	}

protected:
	vsc::IDataTypeStruct				*m_parent;
	int32_t								m_idx;
	std::string							m_name;
	vsc::IDataType						*m_type;
	vsc::TypeFieldAttr					m_attr;
};

} /* namespace arl */

