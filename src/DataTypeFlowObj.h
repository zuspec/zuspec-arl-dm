/*
 * DataTypeFlowObj.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "arl/IDataTypeFlowObj.h"
#include "DataTypeStruct.h"

namespace arl {

class DataTypeFlowObj : public DataTypeStruct, public virtual IDataTypeFlowObj {
public:
	DataTypeFlowObj(
			IContext			*ctxt,
			const std::string	&name,
			FlowObjKindE 		kind);

	virtual ~DataTypeFlowObj();

	virtual FlowObjKindE kind() const override { return m_kind; }

	virtual void accept(vsc::IVisitor *v) override;

private:
	FlowObjKindE					m_kind;
	vsc::ITypeField					*m_poolid;
};

} /* namespace arl */

