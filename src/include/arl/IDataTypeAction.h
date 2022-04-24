/*
 * IDataTypeAction.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IAccept.h"
#include "arl/IDataTypeStruct.h"

namespace arl {

class IDataTypeComponent;

class IDataTypeAction;
using IDataTypeActionUP=std::unique_ptr<IDataTypeAction>;
class IDataTypeAction : public IDataTypeStruct {
public:

	virtual IDataTypeComponent *getComponentType() = 0;

	virtual void setComponentType(IDataTypeComponent *) = 0;

};

}
