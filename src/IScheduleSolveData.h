/*
 * IScheduleSolverData.h
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#pragma once
#include "IScheduleSolveDataVisitor.h"

namespace arl {

class IScheduleSolveData {
public:

	virtual ~IScheduleSolveData() { }

	/**
	 * Apply to a const version of the schedule data. If the applied
	 * data results in a change, a new SolveData will be returned.
	 * If no change results, null will be returned
	 */
	virtual IScheduleSolveData *applyCst(IScheduleSolveData *d) const = 0;

	/**
	 * Apply to a mutable version of the schedule data. The data is
	 * changed in-place and true/false returned based on whether the
	 * applied data resulted in a change.
	 */
	virtual bool applyMut(IScheduleSolveData *d) = 0;

	virtual void accept(IScheduleSolveDataVisitor *v) = 0;

};

}
