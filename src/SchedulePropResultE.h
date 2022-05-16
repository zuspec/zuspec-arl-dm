/*
 * SchedulePropResultE.h
 *
 *  Created on: May 14, 2022
 *      Author: mballance
 */

#pragma once

namespace arl {

enum class SchedulePropResultE {
	/**
	 * Node is SAT and propagation changed the state
	 */
	SatChange,

	/**
	 * Node is still SAT, but no changes resulted
	 */
	SatNoChange,

	/**
	 * Node is now UnSat
	 */
	UnSat
};

}
