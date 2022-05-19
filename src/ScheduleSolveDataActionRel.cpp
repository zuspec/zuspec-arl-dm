/*
 * ScheduleRelSet.cpp
 *
 *  Created on: May 7, 2022
 *      Author: mballance
 */

#include "ScheduleSolveDataActionRel.h"

#include <stdio.h>
#include <string.h>

namespace arl {

ScheduleSolveDataActionRel::ScheduleSolveDataActionRel(int32_t n_actions) : m_n_actions(n_actions) {

	// For simplicity, create storage for all pairs
	uint32_t n_pairs = n_actions*n_actions;
	uint32_t n_elems = ((n_pairs-1)/(2*sizeof(uint32_t)))+1;
	m_rel_l = new uint32_t[n_elems];

	// Initialize where all possibilities are allowed
	memset(m_rel_l, 0xFF, n_elems*sizeof(uint32_t));
}

ScheduleSolveDataActionRel::~ScheduleSolveDataActionRel() {
	delete [] m_rel_l;
}

ScheduleRelE ScheduleSolveDataActionRel::getRel(int32_t i1, int32_t i2) const {
	return static_cast<ScheduleRelE>(get_elem(i1, i2));
}

bool ScheduleSolveDataActionRel::setRel(
		int32_t 		i1,
		int32_t 		i2,
		ScheduleRelE 	rel) {
	std::vector<ScheduleSolveDataActionRel::RelDeltaT>	backtrace;
	bool ret = setRel(backtrace, i1, i2, rel);

	fprintf(stdout, "setRel: %d changes\n", backtrace.size());

	if (!ret) {
		// Reverse changes
		for (std::vector<RelDeltaT>::const_reverse_iterator
				it=backtrace.rbegin();
				it!=backtrace.rend(); it++) {
			set_elem(
					std::get<0>(*it),
					std::get<1>(*it),
					std::get<2>(*it));
		}
	}

	return ret;
}

bool ScheduleSolveDataActionRel::setRel(
		std::vector<RelDeltaT>	&backtrace,
		int32_t 				i1,
		int32_t 				i2,
		ScheduleRelE 			rel) {
	uint32_t ival = static_cast<uint32_t>(rel);
	uint32_t rval = get_elem(i1, i2);

	/**
	 * If the required bits are not already set, then
	 * we cannot keep them set
	 */
	if ((ival & rval) != ival) {
		return false;
	} else if ((ival & rval) != rval) {
		// This is a change
		uint32_t nval = (ival & rval);
		set_elem(i1, i2, nval);

		backtrace.push_back({i1, i2, ival});

		if (nval == static_cast<uint32_t>(ScheduleRelE::SeqAB) ||
				nval == static_cast<uint32_t>(ScheduleRelE::SeqBA)) {
			// Brute-force for now
			for (uint32_t i=0; i<m_n_actions; i++) {
				for (uint32_t j=i+1; j<m_n_actions; j++) {
					for (uint32_t k=j+1; k<m_n_actions; k++) {
						if (getRel(i, j) == ScheduleRelE::SeqAB &&
								getRel(j, k) == ScheduleRelE::SeqAB) {
							if (!setRel(backtrace, i, k, ScheduleRelE::SeqAB)) {
								return false;
							}
						}
					}
				}
			}
		} else if (nval == static_cast<uint32_t>(ScheduleRelE::Par)) {
			// Propagate the parallel
			for (uint32_t i=0; i<m_n_actions; i++) {
				for (uint32_t j=i+1; j<m_n_actions; j++) {
					for (uint32_t k=j+1; k<m_n_actions; k++) {
						if (getRel(i, j) == ScheduleRelE::Par &&
								getRel(j, k) == ScheduleRelE::Par) {
							setRel(backtrace, i, k, ScheduleRelE::Par);
						}
					}
				}
			}
		}
	}
	return true;
}

std::string ScheduleSolveDataActionRel::toString() const {
	char tmp[256];
	std::string ret;

	for (uint32_t i=0; i<m_n_actions; i++) {
		for (uint32_t j=i+1; j<m_n_actions; j++) {
			uint32_t val = get_elem(i, j);
			snprintf(tmp, sizeof(tmp), "[%d,%d]: ", i, j);
			ret += tmp;
			ret += (val & 8)?"1":"0";
			ret += (val & 4)?"1":"0";
			ret += (val & 2)?"1":"0";
			ret += (val & 1)?"1":"0";
			ret += "\n";
		}
	}

	return ret;
}

} /* namespace arl */
