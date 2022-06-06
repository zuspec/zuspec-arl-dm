/*
 * IDataTypeActivityScope.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IDataTypeActivity.h"
#include "vsc/IDataTypeStruct.h"

namespace arl {

class IDataTypeActivityScope : public virtual IDataTypeActivity, public virtual vsc::IDataTypeStruct {
public:

	virtual ~IDataTypeActivityScope() { }

	virtual const std::vector<IDataTypeActivityUP> &getActivities() const = 0;

	virtual void addActivity(IDataTypeActivity *a) = 0;

};

}
