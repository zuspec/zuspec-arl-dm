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

class DataTypeFlowObj : public DataTypeStruct, public virtual IDataTypeFlowObj {
public:
	DataTypeFlowObj(
			const std::string	&name,
			FlowObjKindE 		kind);

	virtual ~DataTypeFlowObj();

	virtual FlowObjKindE kind() const override { return m_kind; }

	virtual void accept(vsc::IVisitor *v) override;

private:
	FlowObjKindE					m_kind;
};

} /* namespace arl */

