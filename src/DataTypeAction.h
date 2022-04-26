/*
 * DataTypeAction.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeAction.h"
#include "DataTypeStruct.h"

namespace arl {

class DataTypeAction : public DataTypeStruct, public virtual IDataTypeAction {
public:
	DataTypeAction(const std::string &name);

	virtual ~DataTypeAction();

	virtual IDataTypeComponent *getComponentType() override {
		return m_component_t;
	}

	virtual void setComponentType(IDataTypeComponent *c) override {
		m_component_t = c;
	}

	virtual void accept(vsc::IVisitor *v) override;

	virtual void accept(IVisitor *v) override;

private:
	IDataTypeComponent					*m_component_t;

};

} /* namespace arl */

