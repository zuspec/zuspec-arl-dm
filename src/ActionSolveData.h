/*
 * ActionSolveData.h
 *
 *  Created on: May 14, 2022
 *      Author: mballance
 */

#pragma once
#include <stdint.h>

namespace arl {

class ActionSolveData {
public:
	ActionSolveData();

	virtual ~ActionSolveData();

private:
	int32_t				m_action_id;

};

} /* namespace arl */

