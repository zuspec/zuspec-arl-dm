/*
 * IDataTypeStruct.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IAccept.h"
#include "arl/IModelStructCreateHook.h"
#include "vsc/IDataTypeStruct.h"

namespace arl {

class IDataTypeStruct : public vsc::IDataTypeStruct, public IAccept {
public:

	virtual ~IDataTypeStruct() { }

	// TODO: exec blocks

};

}
