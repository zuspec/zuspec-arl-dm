/*
 * ScheduleSolveEvalQueue.h
 *
 *  Created on: May 20, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include <unordered_set>
#include "IScheduleSolveEvalQueue.h"
#include "IScheduleSolvePropagator.h"

namespace arl {

class ScheduleSolveEvalQueue : public IScheduleSolveEvalQueue {
public:
	ScheduleSolveEvalQueue();

	virtual ~ScheduleSolveEvalQueue();

	virtual int32_t eval(
			IScheduleSolveEvalQueue *q,
			int32_t					level) override;

	virtual void queueForEval(
			IScheduleSolvePropagator	*src,
			IScheduleSolvePropagator	*dst) override;

private:
	using PropPair=std::pair<IScheduleSolvePropagator*,IScheduleSolvePropagator*>;

private:
	std::vector<PropPair>				m_eval_q;

};

} /* namespace arl */

