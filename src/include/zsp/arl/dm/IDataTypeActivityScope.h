/*
 * IDataTypeActivityScope.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "vsc/dm/ITypeExprFieldRef.h"
#include "zsp/arl/dm/IDataTypeActivity.h"
#include "zsp/arl/dm/ITypeFieldActivity.h"
#include "vsc/dm/IDataTypeStruct.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeActivityScope : 
	public virtual IDataTypeActivity,
	public virtual vsc::dm::IDataTypeStruct {
public:

	virtual ~IDataTypeActivityScope() { }

	virtual const std::vector<ITypeFieldActivityUP> &getActivities() const = 0;

	virtual void addActivity(
        ITypeFieldActivity      *a,
        bool                    owned=true) = 0;

    virtual int32_t getActivityOffset() const = 0;

	virtual void addActivityField(ITypeFieldActivity *a) = 0;

};

}
}
}
