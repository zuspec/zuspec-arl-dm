/*
 * ScheduleSolvePropagatorSingleUni.h
 *
 *  Created on: May 20, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "IScheduleSolveData.h"
#include "IScheduleSolvePropagator.h"
#include "IScheduleSolveNexus.h"

namespace arl {

class ScheduleSolvePropagatorSingleUni : public IScheduleSolvePropagator {
public:
	ScheduleSolvePropagatorSingleUni(
			IScheduleSolveData 		*init,
			int32_t					level=0);

	virtual ~ScheduleSolvePropagatorSingleUni();

	void nexus(IScheduleSolveNexus *n) {
		m_nexus = n;
	}

	IScheduleSolveNexus *nexus() const {
		return m_nexus;
	}

	virtual bool propagate(
			IScheduleSolvePropagator 	*p,
			int32_t						level) override;

	virtual void queueImpactedForEval(IScheduleSolveEvalQueue *q) override;

	virtual void backtrack(int32_t level) override;

	virtual IScheduleSolveData *getData() const override;

private:
	using HistEnt=std::pair<int32_t, IScheduleSolveDataUP>;
	std::vector<HistEnt>			m_history;
	IScheduleSolveNexus				*m_nexus;

};

} /* namespace arl */

