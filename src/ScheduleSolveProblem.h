/*
 * ScheduleSolveProblem.h
 *
 *  Created on: May 21, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include <unordered_map>
#include "ScheduleSolveActionData.h"

namespace arl {

/**
 * Represents the ensire scheduling problem wrt actions
 */
class ScheduleSolveProblem {
public:
	ScheduleSolveProblem();

	virtual ~ScheduleSolveProblem();

private:
	std::vector<ScheduleSolveActionDataUP>		m_actions;
};

} /* namespace arl */

