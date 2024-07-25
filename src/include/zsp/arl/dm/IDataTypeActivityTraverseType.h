/*
 * IDataTypeActivityTraverseType.h
 *
 *  Created on: Jun 18, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeAction.h"
#include "zsp/arl/dm/IDataTypeActivity.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeActivityTraverseType : public virtual IDataTypeActivity {
public:

	virtual ~IDataTypeActivityTraverseType() { }

    virtual IDataTypeAction *getTarget() const = 0;

	virtual vsc::dm::ITypeConstraint *getWithC() const = 0;

	virtual void setWithC(vsc::dm::ITypeConstraint *c) = 0;

};

}
}
}
