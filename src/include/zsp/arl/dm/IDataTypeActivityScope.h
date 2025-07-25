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
#include "zsp/arl/dm/IDataTypeActivityBind.h"
#include "zsp/arl/dm/ITypeFieldActivity.h"
#include "vsc/dm/IDataTypeStruct.h"
#include "vsc/dm/ITypeVarScope.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeActivityScope : 
	public virtual IDataTypeActivity,
    public virtual vsc::dm::ITypeVarScope,
	public virtual vsc::dm::IDataTypeStruct {
public:

	virtual ~IDataTypeActivityScope() { }

	virtual const std::vector<ITypeFieldActivityUP> &getActivities() const = 0;

	virtual void addActivity(
        ITypeFieldActivity      *a,
        bool                    owned=true) = 0;

    virtual int32_t getActivityOffset() const = 0;

	virtual void addActivityField(ITypeFieldActivity *a) = 0;

    virtual const std::vector<IDataTypeActivityBindUP> &getBinds() const = 0;

    virtual void addBind(IDataTypeActivityBind *b) = 0;

    virtual int32_t addVariable(vsc::dm::ITypeVar *var, bool owned=true) override { }

    virtual int32_t getNumVariables() override { return 0; }

    virtual const std::vector<vsc::dm::ITypeVarUP> &getVariables() const override { }

};

}
}
}
