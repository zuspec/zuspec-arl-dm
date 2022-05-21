/*
 * ScheduleSolveDataBase.cpp
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#include "ScheduleSolveDataBase.h"

namespace arl {

ScheduleSolveDataBase::ScheduleSolveDataBase() {
	// TODO Auto-generated constructor stub

}

ScheduleSolveDataBase::~ScheduleSolveDataBase() {
	// TODO Auto-generated destructor stub
}

/**
 * Apply to a const version of the schedule data. If the applied
 * data results in a change, a new SolveData will be returned.
 * If no change results, null will be returned
 */
IScheduleSolveData::Result ScheduleSolveDataBase::applyCst(IScheduleSolvePropagator *d) const {
//	d->accept(const_cast<ScheduleSolveDataBase *>(this));
	return IScheduleSolveData::Result(false, 0);
}

/**
 * Apply to a mutable version of the schedule data. The data is
 * changed in-place and true/false returned based on whether the
 * applied data resulted in a change.
 */
bool ScheduleSolveDataBase::applyMut(IScheduleSolvePropagator *d) {
//	d->accept(this);
	return false;
}

} /* namespace arl */
