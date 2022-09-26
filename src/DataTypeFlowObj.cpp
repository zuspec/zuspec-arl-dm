/*
 * DataTypeFlowObj.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */
#include "arl/IVisitor.h"
#include "DataTypeFlowObj.h"

namespace arl {

DataTypeFlowObj::DataTypeFlowObj(
		const std::string	&name,
		FlowObjKindE 		kind) : DataTypeStruct(name), m_kind(kind) {
	// TODO Auto-generated constructor stub

}

DataTypeFlowObj::~DataTypeFlowObj() {
	// TODO Auto-generated destructor stub
}

void DataTypeFlowObj::accept(vsc::IVisitor *v) {
	if (dynamic_cast<IVisitor *>(v)) {
		dynamic_cast<IVisitor *>(v)->visitDataTypeFlowObj(this);
	} else if (v->cascade()) {
		v->visitDataTypeStruct(this);
	}
}

} /* namespace arl */
