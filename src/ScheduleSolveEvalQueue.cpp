/*
 * ScheduleSolveEvalQueue.cpp
 *
 *  Created on: May 20, 2022
 *      Author: mballance
 */

#include "ScheduleSolveEvalQueue.h"

namespace arl {

ScheduleSolveEvalQueue::ScheduleSolveEvalQueue() {
	// TODO Auto-generated constructor stub

}

ScheduleSolveEvalQueue::~ScheduleSolveEvalQueue() {
	// TODO Auto-generated destructor stub
}

int32_t ScheduleSolveEvalQueue::eval(
		IScheduleSolveEvalQueue 	*q,
		int32_t						level) {
	int32_t changes = 0;

	/*
	for (auto it=m_eval_q.begin(); it!=m_eval_q.end(); it++) {
		bool change = it->second->propagate(it->first);

		if (change) {
			// Collect changes in new eval queue
			it->second->queueImpactedForEval(q);
			changes++;
		}
	}
	 */

	m_eval_q.clear();

	return changes;
}

void ScheduleSolveEvalQueue::queueForEval(
			IScheduleSolvePropagator	*src,
			IScheduleSolvePropagator	*dst) {
	m_eval_q.push_back(PropPair(src,dst));
}

} /* namespace arl */
