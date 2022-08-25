/*
 * DataTypeComponent.h
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeComponent.h"
#include "vsc/IModelFieldFactory.h"
#include "DataTypeStruct.h"

namespace arl {

class DataTypeComponent : 
	public virtual IDataTypeComponent, 
	public virtual DataTypeStruct {
public:
	DataTypeComponent(const std::string &name);

	virtual ~DataTypeComponent();

	virtual const std::vector<IDataTypeAction *> &getActionTypes() const override;

	virtual void addActionType(IDataTypeAction *) override;

	virtual vsc::IModelField *mkRootField(
		vsc::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) override;

	virtual vsc::IModelField *mkTypeField(
		vsc::IModelBuildContext		*ctxt,
		vsc::ITypeField				*type) override;

	virtual void accept(vsc::IVisitor *v) override;

private:
	std::vector<IDataTypeAction *>			m_action_types;
	vsc::IModelStructCreateHookUP			m_create_hook;

};

} /* namespace arl */

