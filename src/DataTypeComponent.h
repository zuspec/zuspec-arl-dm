/*
 * DataTypeComponent.h
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "arl/IDataTypeComponent.h"
#include "vsc/IModelFieldFactory.h"
#include "DataTypeStruct.h"

namespace arl {

class DataTypeComponent : 
	public virtual IDataTypeComponent, 
	public virtual DataTypeStruct {
public:
	DataTypeComponent(
		IContext			*ctxt,
		const std::string 	&name);

	virtual ~DataTypeComponent();

	virtual const std::vector<IDataTypeAction *> &getActionTypes() const override;

	virtual void addActionType(IDataTypeAction *) override;

	virtual void addPoolBindDirective(IPoolBindDirective *bind) override {
		m_pool_binds.push_back(IPoolBindDirectiveUP(bind));
	};

	virtual const std::vector<IPoolBindDirectiveUP> &getPoolBindDirectives() const override {
		return m_pool_binds;
	}

	virtual vsc::IModelField *mkRootField(
		vsc::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) override;

	virtual vsc::IModelField *mkTypeField(
		vsc::IModelBuildContext		*ctxt,
		vsc::ITypeField				*type) override;

	virtual void accept(vsc::IVisitor *v) override;

private:
	vsc::ITypeField							*m_comp_id;
	std::vector<IDataTypeAction *>			m_action_types;
	std::vector<IPoolBindDirectiveUP>		m_pool_binds;
	vsc::IModelStructCreateHookUP			m_create_hook;

};

} /* namespace arl */

