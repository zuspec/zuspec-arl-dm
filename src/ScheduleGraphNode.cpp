/*
 * ScheduleGraphNode.cpp
 *
 *  Created on: May 3, 2022
 *      Author: mballance
 */

#include "ScheduleGraphNode.h"

namespace arl {

ScheduleGraphNode::ScheduleGraphNode(
		vsc::IModelField		*action,
		int32_t					id) : m_action(action), m_id(id) {
	// TODO Auto-generated constructor stub

}

ScheduleGraphNode::~ScheduleGraphNode() {
	// TODO Auto-generated destructor stub
}

bool ScheduleGraphNode::addOutgoingArc(ScheduleGraphNode *dep) {
	return m_outgoing_arc_s.insert(dep).second;
}

void ScheduleGraphNode::delOutgoingArc(ScheduleGraphNode *dep) {
	std::unordered_set<ScheduleGraphNode *>::const_iterator it;

	if ((it=m_outgoing_arc_s.find(dep)) != m_outgoing_arc_s.end()) {
		m_outgoing_arc_s.erase(it);
	}
}

bool ScheduleGraphNode::addIncomingArc(ScheduleGraphNode *dep) {
	return m_incoming_arc_s.insert(dep).second;
}

void ScheduleGraphNode::delIncomingArc(ScheduleGraphNode *dep) {
	std::unordered_set<ScheduleGraphNode *>::const_iterator it;

	if ((it=m_incoming_arc_s.find(dep)) != m_incoming_arc_s.end()) {
		m_incoming_arc_s.erase(it);
	}
}

} /* namespace arl */
