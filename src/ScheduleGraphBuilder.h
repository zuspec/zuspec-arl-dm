/*
 * ScheduleGraphBuilder.h
 *
 *  Created on: May 7, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "ScheduleGraphNode.h"
#include "ScheduleRelSet.h"

namespace arl {

class ScheduleGraphBuilder {
public:
	ScheduleGraphBuilder();

	virtual ~ScheduleGraphBuilder();

	void build(
			std::vector<ScheduleGraphNodeUP>		&nodes,
			const std::vector<vsc::IModelField *>	&actions,
			const ScheduleRelSet					&schedrel);

};

} /* namespace arl */

