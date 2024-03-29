/*
 * DataTypeAction.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <map>
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IDataTypeAction.h"
#include "DataTypeArlStruct.h"

namespace zsp {
namespace arl {
namespace dm {


class DataTypeAction : 
	public virtual IDataTypeAction, 
	public virtual DataTypeArlStruct {
public:
	DataTypeAction(
			IContext			*ctxt,
			const std::string 	&name);

	virtual ~DataTypeAction();

    virtual int32_t getByteSize() const override;

	virtual IDataTypeComponent *getComponentType() override {
		return m_component_t;
	}

	virtual void setComponentType(IDataTypeComponent *c) override;

	virtual vsc::dm::ITypeFieldRef *getCompField() const override { return m_comp; }

	virtual const std::vector<ITypeFieldActivityUP> &activities() const override {
		return m_activities;
	}

	virtual void addActivity(ITypeFieldActivity *activity) override;

    virtual int32_t getActivityOffset() const override;

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
	IDataTypeComponent					            *m_component_t;
	vsc::dm::ITypeFieldRef				            *m_comp;
	std::vector<ITypeFieldActivityUP>	            m_activities;
    int32_t                                         m_activity_sz;

};

}
}
}

