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
#include "ModelFieldComponent.h"
#include "IScheduleSolvePropagator.h"
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
			ModelFieldComponent				*root_comp,
			IDataTypeAction					*root_action);


private:
	IContext								*m_ctxt;
	std::vector<IScheduleSolvePropagatorUP>	m_stage_stack;
	bool									m_complete;

};

} /* namespace arl */

