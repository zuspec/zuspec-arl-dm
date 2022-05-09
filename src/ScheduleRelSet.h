/*
 * ScheduleRelSet.h
 *
 *  Created on: May 7, 2022
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include <string>
#include <tuple>
#include <vector>

namespace arl {

enum class ScheduleRelE {
	SeqAB = 1,
	SeqBA = 2,
	Par   = 4,
	Con   = 8
};

/**
 * Holds relationships between a set of actions
 */
class ScheduleRelSet {
public:
	ScheduleRelSet(int32_t n_actions);

	virtual ~ScheduleRelSet();

	ScheduleRelE getRel(int32_t i1, int32_t i2) const;

	/**
	 * Set the specified relationship bits to be true,
	 * clears others, and propagates the changes.
	 *
	 * Returns 'false' and restores state if the change
	 * cannot be applied
	 */
	bool setRel(int32_t i1, int32_t i2, ScheduleRelE rel);

	std::string toString() const;

private:
	using RelDeltaT=std::tuple<int32_t,int32_t,uint32_t>;

private:
	bool setRel(
			std::vector<RelDeltaT>	&backtrace,
			int32_t 				i1,
			int32_t 				i2,
			ScheduleRelE 			rel);

	inline uint32_t get_elem(int32_t i1, int32_t i2) const {
		return (m_rel_l[((i1*m_n_actions+i2)>>3)] >> ((((i1*m_n_actions+i2)&0x7) << 2))) & 0xF;
	}

	inline void set_elem(int32_t i1, int32_t i2, uint32_t val) {
		m_rel_l[((i1*m_n_actions+i2)>>3)] =
				(m_rel_l[((i1*m_n_actions+i2)>>3)] & ~(0xFULL << (((i1*m_n_actions+i2)&0x7)<<2))) | ((val & 0xF) << (((i1*m_n_actions+i2)&0x7)<<2));
	}

private:
	uint32_t					m_n_actions;
	uint32_t					*m_rel_l;
	std::vector<RelDeltaT>		m_backtrack;

};

} /* namespace arl */

