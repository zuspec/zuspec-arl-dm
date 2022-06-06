/*
 * IScheduleSolvePropagator.h
 *
 *  Created on: May 20, 2022
 *      Author: mballance
 */

#pragma once
#include "IScheduleSolveData.h"

namespace arl {

class IScheduleSolveEvalQueue;

class IScheduleSolvePropagator;
using IScheduleSolvePropagatorUP=std::unique_ptr<IScheduleSolvePropagator>;
class IScheduleSolvePropagator {
public:
	using NextResult=std::pair<bool, IScheduleSolvePropagator *>;
public:

	virtual ~IScheduleSolvePropagator() { }

	virtual bool hasNext() = 0;

	/**
	 * Returns the next iterator if available (should check hasNext before calling)
	 * Returns whether the new propagator should cause a recursion
	 */
	virtual NextResult next() = 0;

	virtual bool propagate(
			IScheduleSolvePropagator 	*p,
			int32_t						level) = 0;

	virtual void queueImpactedForEval(IScheduleSolveEvalQueue *q) = 0;

	virtual void backtrack(int32_t level) = 0;

	virtual IScheduleSolveData *getData() const = 0;


};

}
