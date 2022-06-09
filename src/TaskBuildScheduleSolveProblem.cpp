/*
 * TaskBuildScheduleSolveProblem.cpp
 *
 *  Created on: Jun 8, 2022
 *      Author: mballance
 */

#include "TaskBuildScheduleSolveProblem.h"

namespace arl {

TaskBuildScheduleSolveProblem::TaskBuildScheduleSolveProblem() {
	// TODO Auto-generated constructor stub

}

TaskBuildScheduleSolveProblem::~TaskBuildScheduleSolveProblem() {
	// TODO Auto-generated destructor stub
}

ScheduleSolveProblem *TaskBuildScheduleSolveProblem::build(IModelActivity *activity) {
	m_problem = ScheduleSolveProblemUP(new ScheduleSolveProblem());
	activity->accept(this);
	return m_problem.release();
}

void TaskBuildScheduleSolveProblem::visitModelActivityParallel(IModelActivityParallel *a) {
	VisitorBase::visitModelActivityParallel(a);
}

void TaskBuildScheduleSolveProblem::visitModelActivitySchedule(IModelActivitySchedule *a) {
	VisitorBase::visitModelActivitySchedule(a);
}

void TaskBuildScheduleSolveProblem::visitModelActivitySequence(IModelActivitySequence *a) {
	bool push_new = false;

	if (m_frame_s.size() == 0 || m_frame_s.back().kind != Sequence) {
		m_frame_s.push_back(Frame{Sequence});
		push_new = true;
	}

	VisitorBase::visitModelActivitySequence(a);

	if (push_new) {
		// Add sequential relationships
		const std::vector<ScheduleSolveActionData *> &elems = m_frame_s.back().elems;
		if (elems.size() > 0) {
			for (uint32_t i=0; i<(elems.size()-1); i++) {
				elems.at(i)->node()->addOutgoingArc(
						elems.at(i+1)->node());
				elems.at(i+1)->node()->addIncomingArc(
						elems.at(i)->node());
			}
		}
		m_frame_s.pop_back();
	}
}

void TaskBuildScheduleSolveProblem::visitModelActivityTraverse(IModelActivityTraverse *a) {
	if (m_frame_s.size() == 0) {
		m_frame_s.push_back(Frame{Sequence});
	}
	m_frame_s.back().elems.push_back(m_problem->addActivity(a));
}


} /* namespace arl */
