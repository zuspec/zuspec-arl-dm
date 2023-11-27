/*
 * IModelBuildContext.h
 *
 *  Created on: Jun 13, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IModelActivityScope.h"
#include "vsc/dm/IModelBuildContext.h"

namespace zsp {
namespace arl {
namespace dm {

class IModelBuildContext;
using IModelBuildContextUP=vsc::dm::UP<IModelBuildContext>;
class IModelBuildContext : public virtual vsc::dm::IModelBuildContext {
public:

	virtual ~IModelBuildContext() { }

	virtual arl::dm::IContext *ctxt() const = 0;

	virtual void pushActivityScope(IModelActivityScope *a)  = 0;

	virtual IModelActivityScope *getActivityScope() = 0;

	virtual IModelActivityScope *popActivityScope() = 0;

};

}
}
}
