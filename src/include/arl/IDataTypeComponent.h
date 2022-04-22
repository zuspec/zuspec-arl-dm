/*
 * IDataTypeComponent.h
 *
 *  Created on: Apr 20, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IAccept.h"
#include "vsc/IDataTypeStruct.h"

namespace arl {

class IDataTypeComponent;
using IDataTypeComponentUP=std::unique_ptr<IDataTypeComponent>;
class IDataTypeComponent : public vsc::IDataTypeStruct, public IAccept {
public:

	virtual ~IDataTypeComponent() { }

};

}
