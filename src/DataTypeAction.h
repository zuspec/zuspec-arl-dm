/*
 * DataTypeAction.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "arl/IDataTypeAction.h"
#include "DataTypeStruct.h"
#include "include/arl/sav/ITypeActivityStmt.h"

namespace arl {

class DataTypeAction : public DataTypeStruct, public virtual IDataTypeAction {
public:
	DataTypeAction(
			IContext			*ctxt,
			const std::string 	&name);

	virtual ~DataTypeAction();

	virtual IDataTypeComponent *getComponentType() override {
		return m_component_t;
	}

	virtual void setComponentType(IDataTypeComponent *c) override;

	virtual const std::vector<IDataTypeActivityUP> &activities() const override {
		return m_activities;
	}

	virtual void addActivity(IDataTypeActivity *activity) {
		m_activities.push_back(IDataTypeActivityUP(activity));
	}

	virtual void accept(vsc::IVisitor *v) override;

private:
	IDataTypeComponent					*m_component_t;
	std::vector<IDataTypeActivityUP>	m_activities;

};

} /* namespace arl */

