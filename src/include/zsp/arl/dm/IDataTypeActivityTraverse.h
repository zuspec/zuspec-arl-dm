/*
 * IDataTypeActivityTraverse.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeActivity.h"
#include "vsc/dm/ITypeConstraint.h"
#include "vsc/dm/ITypeExprFieldRef.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeActivityTraverse : public virtual IDataTypeActivity {
public:

	virtual ~IDataTypeActivityTraverse() { }

	virtual vsc::dm::ITypeExpr *getTarget() const = 0;

	virtual vsc::dm::ITypeConstraint *getWithC() const = 0;

	virtual void setWithC(vsc::dm::ITypeConstraint *c) = 0;

};

}
}
}
