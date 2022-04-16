/*
 * DataTypeFlowObj.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeFlowObj.h"
#include "DataTypeStruct.h"

namespace arl {

class DataTypeFlowObj : public DataTypeStruct, public IDataTypeFlowObj {
public:
	DataTypeFlowObj(
			const std::string	&name,
			FlowObjKindE 		kind);

	virtual ~DataTypeFlowObj();

	virtual FlowObjKindE kind() const override { return m_kind; }

	virtual void accept(vsc::IVisitor *v) override {
		if (dynamic_cast<IVisitor *>(v)) {
			dynamic_cast<IVisitor *>(v)->visitDataTypeFlowObj(this);
		} else {
			v->visitDataTypeStruct(this);
		}
	}

	virtual void accept(IVisitor *v) override { v->visitDataTypeFlowObj(this); }

private:
	FlowObjKindE					m_kind;
};

} /* namespace arl */

