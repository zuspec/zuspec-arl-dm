/*
 * ScheduleGraphArcTrimmer.cpp
 *
 *  Created on: May 3, 2022
 *      Author: mballance
 */

#include "ScheduleGraphArcTrimmer.h"

namespace arl {

ScheduleGraphArcTrimmer::ScheduleGraphArcTrimmer() {
	// TODO Auto-generated constructor stub

}

ScheduleGraphArcTrimmer::~ScheduleGraphArcTrimmer() {
	// TODO Auto-generated destructor stub
}

void ScheduleGraphArcTrimmer::trim(const std::vector<ScheduleGraphNodeUP> &nodes) {
	for (auto it=nodes.begin(); it!=nodes.end(); it++) {
		processNode(it->get());
	}
}

void ScheduleGraphArcTrimmer::processNode(ScheduleGraphNode *node) {
	// We must evaluate all outgoing arcs to determine whether
	// the target node can be reached via another path

	std::unordered_set<ScheduleGraphNode *> remove_node_s;

	for (auto it1=node->getOutgoingArcs().begin();
			it1!=node->getOutgoingArcs().end(); it1++) {
		for (auto it2=node->getOutgoingArcs().begin();
				it2!=node->getOutgoingArcs().end(); it2++) {
			if (it1 != it2) {
				// See if we can reach the target of it1 via
				// it2
				if (canReachVia(*it1, *it2)) {
					// Remove the direct path
					remove_node_s.insert(*it1);
				}
			}
		}
	}

	for (auto it=remove_node_s.begin(); it!=remove_node_s.end(); it++) {
		(*it)->delIncomingArc(node);
		node->delOutgoingArc(*it);
	}

	// Now, tree out
	for (auto it=node->getOutgoingArcs().begin();
			it!=node->getOutgoingArcs().end(); it++) {
		processNode(*it);
	}
}

bool ScheduleGraphArcTrimmer::canReachVia(
			ScheduleGraphNode *target,
			ScheduleGraphNode *via) {
	// Check direct first
	for (auto it=via->getOutgoingArcs().begin();
			it!=via->getOutgoingArcs().end(); it++) {
		if (target == *it) {
			return true;
		}
	}

	// Check indirect next
	for (auto it=via->getOutgoingArcs().begin();
			it!=via->getOutgoingArcs().end(); it++) {
		if (canReachVia(target, *it)) {
			return true;
		}
	}
	return false;
}

} /* namespace arl */
