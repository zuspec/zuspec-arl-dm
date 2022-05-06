/*
 * ScheduleGraphArcTrimmer.h
 *
 *  Created on: May 3, 2022
 *      Author: mballance
 */
#pragma once
#include <vector>
#include "ScheduleGraphNode.h"

namespace arl {

/**
 * Removes redundant arcs from the graph
 */
class ScheduleGraphArcTrimmer {
public:
	ScheduleGraphArcTrimmer();

	virtual ~ScheduleGraphArcTrimmer();

	void trim(const std::vector<ScheduleGraphNodeUP> &nodes);

private:

	void processNode(ScheduleGraphNode *node);

	bool canReachVia(
			ScheduleGraphNode *target,
			ScheduleGraphNode *via);

};

} /* namespace arl */

