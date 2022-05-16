/*
 * ScheduleSolveDataBaseVisitor.h
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#pragma once
#include "IScheduleSolveDataVisitor.h"

namespace arl {

class ScheduleSolveDataBaseVisitor : public IScheduleSolveDataVisitor {
public:
	ScheduleSolveDataBaseVisitor();

	virtual ~ScheduleSolveDataBaseVisitor();

};

} /* namespace arl */

