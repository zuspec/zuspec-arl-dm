/*
 * IDataTypeActivityTraverse.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeActivity.h"
#include "vsc/ITypeConstraint.h"
#include "vsc/ITypeExprFieldRef.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeActivityTraverse : public virtual IDataTypeActivity {
public:

	virtual ~IDataTypeActivityTraverse() { }

	virtual vsc::ITypeExprFieldRef *getTarget() const = 0;

	virtual vsc::ITypeConstraint *getWithC() const = 0;

	virtual void setWithC(vsc::ITypeConstraint *c) = 0;

};

}
}
}
