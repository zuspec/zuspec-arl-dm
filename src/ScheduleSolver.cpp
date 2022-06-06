/*
 * ScheduleSolver.cpp
 *
 *  Created on: May 14, 2022
 *      Author: mballance
 */

#include "ScheduleSolver.h"
#include "ScheduleSolveEvalQueue.h"

namespace arl {

ScheduleSolver::ScheduleSolver(IContext *ctxt) : m_ctxt(ctxt) {
	m_complete = false;

}

ScheduleSolver::~ScheduleSolver() {
	// TODO Auto-generated destructor stub
}

std::pair<ExecGraphNode *, std::string> ScheduleSolver::solve(
			ModelFieldRootComponent			*root_comp,
			IDataTypeAction					*root_action) {
	ScheduleSolveEvalQueue *qn = new ScheduleSolveEvalQueue();
	ScheduleSolveEvalQueue *qp = new ScheduleSolveEvalQueue();

	// TODO: Create initial stage

	while (m_stage_stack.size() > 0 && m_complete) {

		uint32_t level = m_stage_stack.size();

		IScheduleSolvePropagator::NextResult next =
				m_stage_stack.back()->next();

		if (next.first) {
			m_stage_stack.push_back(IScheduleSolvePropagatorUP(next.second));
		} else {
			//
		}


//		m_stage_stack.back()->

	}
	;


}

} /* namespace arl */
