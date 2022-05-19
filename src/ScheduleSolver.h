/*
 * ScheduleSolver.h
 *
 *  Created on: May 14, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IContext.h"
#include "ExecGraphNode.h"
#include "IScheduleSolveStage.h"
#include "ModelFieldRootComponent.h"
#include "ScheduleSolveStage.h"

namespace arl {

class ScheduleSolver {
public:
	ScheduleSolver(IContext *ctxt);

	virtual ~ScheduleSolver();

	/**
	 * Returns an execution graph containing model fields.
	 * The graph owns all action instances
	 */
	std::pair<ExecGraphNode *, std::string> solve(
			ModelFieldRootComponent			*root_comp,
			IDataTypeAction					*root_action);


private:
	IContext								*m_ctxt;
	std::vector<IScheduleSolveStageUP>		m_stage_stack;
};

} /* namespace arl */

