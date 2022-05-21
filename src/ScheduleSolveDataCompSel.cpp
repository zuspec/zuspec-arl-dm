/*
 * ScheduleSolveDataCompSel.cpp
 *
 *  Created on: May 20, 2022
 *      Author: mballance
 */

#include "ScheduleSolveDataCompSel.h"

namespace arl {

ScheduleSolveDataCompSel::ScheduleSolveDataCompSel(
		const std::vector<int32_t> &comp_id_l) :
			m_comp_id_l(comp_id_l.begin(), comp_id_l.end()) {
	// TODO Auto-generated constructor stub

}

ScheduleSolveDataCompSel::~ScheduleSolveDataCompSel() {
	// TODO Auto-generated destructor stub
}

IScheduleSolveData::Result ScheduleSolveDataCompSel::applyCst(
		IScheduleSolvePropagator *p) const {
	;
}

	/**
	 * Apply to a mutable version of the schedule data. The data is
	 * changed in-place and true/false returned based on whether the
	 * applied data resulted in a change.
	 */
bool ScheduleSolveDataCompSel::applyMut(IScheduleSolvePropagator *d) {

}

} /* namespace arl */
