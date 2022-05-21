/*
 * IScheduleSolveNexus.h
 *
 *  Created on: May 20, 2022
 *      Author: mballance
 */

#pragma once

namespace arl {

class IScheduleSolvePropagator;
class IScheduleSolveEvalQueue;

class IScheduleSolveNexus {
public:

	virtual ~IScheduleSolveNexus() { }

	/**
	 * Queue propagators that would be impacted by a change in 'p'
	 * for future evaluation
	 */
	virtual void queueImpactedForEval(
			IScheduleSolveEvalQueue		*q,
			IScheduleSolvePropagator 	*p) = 0;
};
}




