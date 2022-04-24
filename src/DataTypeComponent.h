/*
 * DataTypeComponent.h
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeComponent.h"
#include "DataTypeStruct.h"

namespace arl {

class DataTypeComponent : public IDataTypeComponent {
public:
	DataTypeComponent(const std::string &name);

	virtual ~DataTypeComponent();

	virtual const std::string &name() const {
		return m_name;
	}

	virtual void addField(vsc::ITypeField *f);

	virtual const std::vector<vsc::ITypeFieldUP> &getFields() const {
		return m_fields;
	}

	virtual vsc::ITypeField *getField(int32_t idx) {
		return m_fields.at(idx).get();
	}

	virtual void addConstraint(vsc::ITypeConstraint *c);

	virtual const std::vector<vsc::ITypeConstraintUP> &getConstraints() const {
		return m_constraints;
	}

	virtual vsc::IModelStructCreateHook *getCreateHook() const override;

	virtual void setCreateHook(vsc::IModelStructCreateHook *hook) override;

	virtual const std::vector<IDataTypeAction *> &getActionTypes() const override;

	virtual void addActionType(IDataTypeAction *) override;

	virtual void accept(vsc::IVisitor *v) override;

	virtual void accept(IVisitor *v) override { /* TODO: v->visitDataTypeComponent(this); */ }

private:
	std::string								m_name;
	std::vector<vsc::ITypeFieldUP>		 	m_fields;
	std::vector<vsc::ITypeConstraintUP>		m_constraints;
	std::vector<IDataTypeAction *>			m_action_types;
	vsc::IModelStructCreateHookUP			m_create_hook;

};

} /* namespace arl */

