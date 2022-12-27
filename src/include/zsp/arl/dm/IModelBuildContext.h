/*
 * IModelBuildContext.h
 *
 *  Created on: Jun 13, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "arl/IModelActivityScope.h"
#include "vsc/IModelBuildContext.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelBuildContext : public virtual vsc::IModelBuildContext {
public:

	virtual ~IModelBuildContext() { }

	virtual arl::IContext *ctxt() const = 0;

	virtual void pushActivityScope(IModelActivityScope *a)  = 0;

	virtual IModelActivityScope *getActivityScope() = 0;

	virtual IModelActivityScope *popActivityScope() = 0;

};

}
}
}
