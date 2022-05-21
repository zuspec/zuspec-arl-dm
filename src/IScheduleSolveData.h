/*
 * IScheduleSolverData.h
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "IScheduleSolveDataVisitor.h"

namespace arl {

class IScheduleSolvePropagator;

class IScheduleSolveData;
using IScheduleSolveDataUP=std::unique_ptr<IScheduleSolveData>;
class IScheduleSolveData {
public:

	using Result=std::pair<bool,IScheduleSolveData*>;
public:

	virtual ~IScheduleSolveData() { }

	/**
	 * Apply to a const version of the schedule data. If the applied
	 * data results in a change, a new SolveData will be returned.
	 * If no change results, null will be returned
	 *
	 * Propagator is passed here, since the same type of data may
	 * mean different things when applied
	 */
	virtual std::pair<bool,IScheduleSolveData *> applyCst(IScheduleSolvePropagator *p) const = 0;

	/**
	 * Apply to a mutable version of the schedule data. The data is
	 * changed in-place and true/false returned based on whether the
	 * applied data resulted in a change.
	 */
	virtual bool applyMut(IScheduleSolvePropagator *d) = 0;

//	virtual void accept(IScheduleSolveDataVisitor *v) = 0;

};

}
