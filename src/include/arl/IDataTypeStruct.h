/*
 * IDataTypeStruct.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelStructCreateHook.h"
#include "vsc/IDataTypeStruct.h"

namespace arl {

class IDataTypeStruct : vsc::IDataTypeStruct {
public:

	virtual ~IDataTypeStruct() { }

	virtual void setCreateHook(IModelStructCreateHook *hook) = 0;

};

}
