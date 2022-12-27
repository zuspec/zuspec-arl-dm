/*
 * IDataTypeActivityScope.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/ITypeExprFieldRef.h"
#include "arl/IDataTypeActivity.h"
#include "arl/ITypeFieldActivity.h"
#include "vsc/IDataTypeStruct.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeActivityScope : 
	public virtual IDataTypeActivity,
	public virtual vsc::IDataTypeStruct {
public:

	virtual ~IDataTypeActivityScope() { }

	virtual const std::vector<ITypeFieldActivity *> &getActivities() const = 0;

	virtual void addActivity(ITypeFieldActivity *a) = 0;

	virtual void addActivityField(ITypeFieldActivity *a) = 0;

};

}
}
}
