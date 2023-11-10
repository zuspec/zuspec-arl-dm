/*
 * ModelField.h
 *
 *  Created on: Jun 18, 2022
 *      Author: mballance
 */
#pragma once
#include "vsc/dm/IModelField.h"
#include "vsc/dm/impl/ValRef.h"

namespace zsp {
namespace arl {
namespace dm {


class ModelField : public virtual vsc::dm::IModelField {
public:
	ModelField();

	virtual ~ModelField();

	virtual vsc::dm::IModelField *getParent() const override {
		return m_parent;
	}

	virtual void setParent(vsc::dm::IModelField *p) override {
		m_parent = p;
	}

	virtual void setDataType(vsc::dm::IDataType *t) override { }

	virtual const std::vector<vsc::dm::IModelConstraintUP> &getConstraints() const override {
		return m_constraints;
	}

	virtual void addConstraint(
        vsc::dm::IModelConstraint   *c,
        bool                        owned) override;

	virtual const std::vector<vsc::dm::IModelFieldUP> &getFields() const override {
		return m_fields;
	}

	virtual void addField(
        vsc::dm::IModelField    *field,
        bool                    owned) override;

	virtual vsc::dm::IModelField *getField(int32_t idx) override;

	virtual vsc::dm::ValRef getImmVal() const override {
        return m_val.toImmutable();
	}

	virtual vsc::dm::ValRef getMutVal() const override {
        return m_val.toMutable();
	}

	virtual vsc::dm::ModelFieldFlag flags() const override {
		return m_flags;
	}

	virtual void clearFlag(vsc::dm::ModelFieldFlag flags) override {
		m_flags = (m_flags & (~flags));
	}

	virtual void setFlag(vsc::dm::ModelFieldFlag flags) override {
		m_flags = (m_flags | flags);
	}

	virtual void setFlags(vsc::dm::ModelFieldFlag flags) override {
		m_flags = flags;
	}

	virtual bool isFlagSet(vsc::dm::ModelFieldFlag flags) const override {
		return ((m_flags & flags) == flags);
	}

	virtual void setFieldData(vsc::dm::IModelFieldData *data) override {
		m_data = vsc::dm::IModelFieldDataUP(data);
	}

	virtual vsc::dm::IModelFieldData *getFieldData() override {
		return m_data.get();
	}

protected:
	vsc::dm::IModelField						*m_parent;
	vsc::dm::IModelFieldDataUP					m_data;
    vsc::dm::ValRef                             m_val;

	std::vector<vsc::dm::IModelFieldUP>			m_fields;
	std::vector<vsc::dm::IModelConstraintUP>	m_constraints;
	vsc::dm::ModelFieldFlag						m_flags;
};

}
}
}

