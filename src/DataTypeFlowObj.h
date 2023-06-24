/*
 * DataTypeFlowObj.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeFlowObj.h"
#include "DataTypeArlStruct.h"

namespace zsp {
namespace arl {
namespace dm {


class DataTypeFlowObj : 
    public virtual IDataTypeFlowObj,
    public virtual DataTypeArlStruct {
public:
	DataTypeFlowObj(
			IContext			*ctxt,
			const std::string	&name,
			FlowObjKindE 		kind);

	virtual ~DataTypeFlowObj();

	virtual FlowObjKindE kind() const override { return m_kind; }

	virtual void accept(vsc::dm::IVisitor *v) override;

private:
	FlowObjKindE					m_kind;
	vsc::dm::ITypeField				*m_poolid;
};

}
}
}

