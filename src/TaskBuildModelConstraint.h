/*
 * TaskBuildModelConstraint.h
 *
 *  Created on: Jun 17, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IModelBuildContext.h"
#include "vsc/dm/impl/TaskBuildModelConstraint.h"

namespace zsp {
namespace arl {
namespace dm {


class TaskBuildModelConstraint : public vsc::dm::TaskBuildModelConstraint<> {
public:
	TaskBuildModelConstraint(IModelBuildContext *ctxt);

	virtual ~TaskBuildModelConstraint();

};

}
}
}

