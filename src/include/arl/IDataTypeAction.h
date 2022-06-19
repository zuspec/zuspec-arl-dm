/*
 * IDataTypeAction.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IAccept.h"
#include "arl/ITypeFieldActivity.h"
#include "vsc/IDataTypeStruct.h"

namespace arl {

class IDataTypeComponent;

class IDataTypeAction;
using IDataTypeActionUP=std::unique_ptr<IDataTypeAction>;
class IDataTypeAction : public virtual vsc::IDataTypeStruct {
public:

	virtual IDataTypeComponent *getComponentType() = 0;

	virtual void setComponentType(IDataTypeComponent *) = 0;

	virtual const std::vector<ITypeFieldActivity *> &activities() const = 0;

	virtual void addActivity(ITypeFieldActivity *activity) = 0;

};

}
