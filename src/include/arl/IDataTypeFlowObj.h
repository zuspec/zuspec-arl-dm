/*
 * IDataTypeFlowObj.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IAccept.h"
#include "vsc/IDataTypeStruct.h"

namespace arl {

enum class FlowObjKindE {
	Buffer,
	Resource,
	State,
	Stream
};

class IDataTypeFlowObj : public vsc::IDataTypeStruct, public IAccept {
public:

	virtual ~IDataTypeFlowObj() { }

	virtual FlowObjKindE kind() const = 0;

};

}
