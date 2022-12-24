/*
 * IDataTypeComponent.h
 *
 *  Created on: Apr 20, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IAccept.h"
#include "arl/IPoolBindDirective.h"
#include "vsc/IDataTypeStruct.h"

namespace arl {

class IDataTypeAction;

class IDataTypeComponent;
using IDataTypeComponentUP=std::unique_ptr<IDataTypeComponent>;
class IDataTypeComponent : public virtual vsc::IDataTypeStruct {
public:

	virtual ~IDataTypeComponent() { }

	virtual const std::vector<IDataTypeAction *> &getActionTypes() const = 0;

	virtual void addActionType(IDataTypeAction *) = 0;

	virtual void addPoolBindDirective(IPoolBindDirective *bind) = 0;

	virtual const std::vector<IPoolBindDirectiveUP> &getPoolBindDirectives() const = 0;

};

}
