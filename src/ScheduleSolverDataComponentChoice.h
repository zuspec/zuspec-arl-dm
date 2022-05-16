/*
 * ScheduleSolverDataComponentChoice.h
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include <vector>
#include "ComponentMap.h"
#include "ScheduleSolveDataBase.h"

namespace arl {

class ScheduleSolverDataComponentChoice : public ScheduleSolveDataBase {
public:
	ScheduleSolverDataComponentChoice(const ComponentMap &cm);

	virtual ~ScheduleSolverDataComponentChoice();

private:
	const ComponentMap				&m_comp_m;
	std::vector<int32_t>			m_valid_components;

};

} /* namespace arl */

