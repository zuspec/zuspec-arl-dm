/*
 * DataTypeComponent.h
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IDataTypeComponent.h"
#include "vsc/dm/IModelFieldFactory.h"
#include "DataTypeArlStruct.h"

namespace zsp {
namespace arl {
namespace dm {


class DataTypeComponent : 
	public virtual IDataTypeComponent, 
	public DataTypeArlStruct {
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

	virtual vsc::dm::IModelField *mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) override;

	virtual vsc::dm::IModelField *mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type,
        const vsc::dm::ValRef           &val) override;

	virtual void accept(vsc::dm::IVisitor *v) override;

private:
	vsc::dm::ITypeField							*m_comp_id;
	std::vector<IDataTypeAction *>			m_action_types;
	std::vector<IPoolBindDirectiveUP>		m_pool_binds;
	vsc::dm::IModelStructCreateHookUP			m_create_hook;

};

}
}
}

