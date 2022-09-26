/*
 * IDataTypeFlowObj.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IDataTypeStruct.h"

namespace arl {

enum class FlowObjKindE {
	Buffer,
	Resource,
	State,
	Stream
};

class IDataTypeFlowObj;
using IDataTypeFlowObjUP=std::unique_ptr<IDataTypeFlowObj>;
class IDataTypeFlowObj : public virtual vsc::IDataTypeStruct {
public:

	virtual ~IDataTypeFlowObj() { }

	virtual FlowObjKindE kind() const = 0;

};

}
