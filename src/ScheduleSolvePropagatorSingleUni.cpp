/*
 * ScheduleSolvePropagatorSingleUni.cpp
 *
 *  Created on: May 20, 2022
 *      Author: mballance
 */

#include "ScheduleSolvePropagatorSingleUni.h"

namespace arl {

ScheduleSolvePropagatorSingleUni::ScheduleSolvePropagatorSingleUni(
		IScheduleSolveData 		*init,
		int32_t					level) {
	m_history.push_back(HistEnt(level, IScheduleSolveDataUP(init)));
}

ScheduleSolvePropagatorSingleUni::~ScheduleSolvePropagatorSingleUni() {
	// TODO Auto-generated destructor stub
}

bool ScheduleSolvePropagatorSingleUni::propagate(
			IScheduleSolvePropagator 	*p,
			int32_t						level) {
	bool ret = false;

	if (level <= m_history.back().first) { // Last entry is considered mutable
		ret = m_history.back().second.get()->applyMut(p);
	} else { // Last entry is from the previous level
		IScheduleSolveData::Result  p_ret = m_history.back().second.get()->applyCst(p);

		ret = p_ret.first;

		if (p_ret.second) {
			m_history.push_back({level, IScheduleSolveDataUP(p_ret.second)});
		}
	}

	return ret;
}

void ScheduleSolvePropagatorSingleUni::queueImpactedForEval(
		IScheduleSolveEvalQueue *q) {
	//

}

void ScheduleSolvePropagatorSingleUni::backtrack(int32_t level) {
	while (m_history.back().first > level) {
		m_history.pop_back();
	}
}

IScheduleSolveData *ScheduleSolvePropagatorSingleUni::getData() const {
	return m_history.back().second.get();
}

} /* namespace arl */
