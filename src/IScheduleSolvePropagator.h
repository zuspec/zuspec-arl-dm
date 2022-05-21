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

class IScheduleSolvePropagator {
public:
public:

	virtual ~IScheduleSolvePropagator() { }

	virtual bool propagate(
			IScheduleSolvePropagator 	*p,
			int32_t						level) = 0;

	virtual void queueImpactedForEval(IScheduleSolveEvalQueue *q) = 0;

	virtual void backtrack(int32_t level) = 0;

	virtual IScheduleSolveData *getData() const = 0;


};

}
