/*
 * IModelBuildContext.h
 *
 *  Created on: Jun 13, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "vsc/IModelBuildContext.h"

namespace arl {

class IModelBuildContext : public virtual vsc::IModelBuildContext {
public:

	virtual ~IModelBuildContext() { }

	virtual arl::IContext *ctxt() const = 0;

};

}
