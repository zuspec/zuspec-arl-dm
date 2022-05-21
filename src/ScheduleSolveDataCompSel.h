/*
 * ScheduleSolveDataCompSel.h
 *
 *  Created on: May 20, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "IScheduleSolveData.h"

namespace arl {

class ScheduleSolveDataCompSel : public IScheduleSolveData {
public:
	ScheduleSolveDataCompSel(const std::vector<int32_t> &comp_id_l);

	virtual ~ScheduleSolveDataCompSel();

	/**
	 * Apply to a const version of the schedule data. If the applied
	 * data results in a change, a new SolveData will be returned.
	 * If no change results, null will be returned
	 *
	 * Propagator is passed here, since the same type of data may
	 * mean different things when applied
	 */
	virtual IScheduleSolveData::Result applyCst(IScheduleSolvePropagator *p) const override;

	/**
	 * Apply to a mutable version of the schedule data. The data is
	 * changed in-place and true/false returned based on whether the
	 * applied data resulted in a change.
	 */
	virtual bool applyMut(IScheduleSolvePropagator *d) override;


private:
	std::vector<int32_t>		m_comp_id_l;
};

} /* namespace arl */

