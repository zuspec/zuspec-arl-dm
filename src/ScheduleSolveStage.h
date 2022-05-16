/*
 * ScheduleSolveStage.h
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <vector>
#include "IScheduleSolveChoice.h"

namespace arl {

class ScheduleSolveStage;
using ScheduleSolveStageUP=std::unique_ptr<ScheduleSolveStage>;
class ScheduleSolveStage {
public:
	ScheduleSolveStage(ScheduleSolveStage *prev);

	virtual ~ScheduleSolveStage();

private:
	ScheduleSolveStage						*m_prev;
	std::vector<IScheduleSolveChoice *>		m_choice_s;

};

} /* namespace arl */

