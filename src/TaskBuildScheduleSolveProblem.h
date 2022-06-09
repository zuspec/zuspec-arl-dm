/*
 * TaskBuildScheduleSolveProblem.h
 *
 *  Created on: Jun 8, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/impl/VisitorBase.h"
#include "ScheduleSolveActionData.h"
#include "ScheduleSolveProblem.h"

namespace arl {

class TaskBuildScheduleSolveProblem : public VisitorBase {
public:

	TaskBuildScheduleSolveProblem();

	virtual ~TaskBuildScheduleSolveProblem();

	ScheduleSolveProblem *build(IModelActivity *activity);

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override;

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override;

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

private:
	enum Kind {
		Parallel,
		Schedule,
		Sequence
	};
	struct Frame {
		Kind									kind;
		std::vector<ScheduleSolveActionData *>	elems;
	};


private:
	ScheduleSolveProblemUP				m_problem;
	std::vector<Frame>					m_frame_s;

};

} /* namespace arl */

