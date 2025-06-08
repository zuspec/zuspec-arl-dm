/*
 * IDataTypeComponent.h
 *
 *  Created on: Apr 20, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "zsp/arl/dm/IAccept.h"
#include "zsp/arl/dm/IPoolBindDirective.h"
#include "zsp/arl/dm/IDataTypeArlStruct.h"
#include "zsp/arl/dm/ITypeFieldActivity.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeAction;

class IDataTypeComponent;
using IDataTypeComponentUP=vsc::dm::UP<IDataTypeComponent>;
class IDataTypeComponent : public virtual arl::dm::IDataTypeArlStruct {
public:

	virtual ~IDataTypeComponent() { }

	virtual const std::vector<IDataTypeAction *> &getActionTypes() const = 0;

	virtual void addActionType(IDataTypeAction *) = 0;

	virtual void addPoolBindDirective(IPoolBindDirective *bind) = 0;

	virtual const std::vector<IPoolBindDirectiveUP> &getPoolBindDirectives() const = 0;

	virtual const std::vector<ITypeFieldActivityUP> &activities() const = 0;

	virtual void addActivity(ITypeFieldActivity *activity) = 0;

};

}
}
}
