/*
 * TypeField.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class TypeField : public virtual vsc::dm::ITypeField {
public:
	TypeField(
			const std::string			&name,
			vsc::dm::IDataType				*type,
			bool						owned,
			vsc::dm::TypeFieldAttr			attr);

	virtual ~TypeField();

	virtual vsc::dm::ITypeField *getParent() const override {
		return m_parent;
	}

	virtual void setParent(vsc::dm::ITypeField *p) override {
		m_parent = p;
	}

	virtual int32_t getIndex() const override { return m_idx; }

	virtual void setIndex(int32_t idx) override { m_idx = idx; }

	virtual const std::string &name() const { return m_name; }

	virtual vsc::dm::IDataType *getDataType() const override {
		return m_type;
	}

	virtual void setDataType(vsc::dm::IDataType *t, bool own=false) override {
		m_type = t;
		if (own) {
			m_type_owned = vsc::dm::IDataTypeUP(t);
		}
	}

    virtual bool isDataTypeOwned() const override { 
        return m_type_owned.get();
    }

	virtual vsc::dm::ITypeField *getField(int32_t idx) const override;

	virtual vsc::dm::TypeFieldAttr getAttr() const override {
		return m_attr;
	}

	virtual vsc::dm::IModelField *mkModelField(
		vsc::dm::IModelBuildContext 			*ctxt) override;

protected:
	vsc::dm::ITypeField						*m_parent;
	int32_t								    m_idx;
	std::string							    m_name;
	vsc::dm::IDataType						*m_type;
	vsc::dm::IDataTypeUP					m_type_owned;
	vsc::dm::TypeFieldAttr					m_attr;
};

}
}
}

