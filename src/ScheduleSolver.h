/*
 * ScheduleSolver.h
 *
 *  Created on: May 14, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "ScheduleSolveStage.h"

namespace arl {

class ScheduleSolver {
public:
	ScheduleSolver(IContext *ctxt);

	virtual ~ScheduleSolver();


private:
	IContext				*m_ctxt;
	ScheduleSolveStageUP	m_active_stage;
};

} /* namespace arl */

