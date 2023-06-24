/*
 * IDataTypeFlowObj.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeArlStruct.h"

namespace zsp {
namespace arl {
namespace dm {


enum class FlowObjKindE {
	Buffer,
	Resource,
	State,
	Stream
};

class IDataTypeFlowObj;
using IDataTypeFlowObjUP=vsc::dm::UP<IDataTypeFlowObj>;
class IDataTypeFlowObj : public virtual arl::dm::IDataTypeArlStruct {
public:

	virtual ~IDataTypeFlowObj() { }

	virtual FlowObjKindE kind() const = 0;

};

}
}
}
