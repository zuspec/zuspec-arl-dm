/*
 * ScheduleSolveDataBase.h
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#pragma once
#include "IScheduleSolveData.h"
#include "ScheduleSolveDataBaseVisitor.h"

namespace arl {

class ScheduleSolveDataBase :
		public ScheduleSolveDataBaseVisitor,
		public IScheduleSolveData {
public:
	ScheduleSolveDataBase();

	virtual ~ScheduleSolveDataBase();

	/**
	 * Apply to a const version of the schedule data. If the applied
	 * data results in a change, a new SolveData will be returned.
	 * If no change results, null will be returned
	 */
	virtual IScheduleSolveData *applyCst(IScheduleSolveData *d) const override;

	/**
	 * Apply to a mutable version of the schedule data. The data is
	 * changed in-place and true/false returned based on whether the
	 * applied data resulted in a change.
	 */
	virtual bool applyMut(IScheduleSolveData *d) override;

protected:

};

} /* namespace arl */

