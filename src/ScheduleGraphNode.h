/*
 * ScheduleGraphNode.h
 *
 *  Created on: May 3, 2022
 *      Author: mballance
 */

#pragma once
#include <unordered_set>
#include <vector>
#include "vsc/IModelField.h"

namespace arl {

class ScheduleGraphNode {
public:
	ScheduleGraphNode(
			vsc::IModelField		*action,
			int32_t					id
			);

	virtual ~ScheduleGraphNode();

	vsc::IModelField *action() const { return m_action; }

	int32_t id() const { return m_id; }

	bool addOutgoingArc(ScheduleGraphNode *dep);

	void delOutgoingArc(ScheduleGraphNode *dep);

	const std::unordered_set<ScheduleGraphNode *> &getOutgoingArcs() const {
		return m_outgoing_arc_s;
	}

	bool addIncomingArc(ScheduleGraphNode *dep);

	void delIncomingArc(ScheduleGraphNode *dep);

	const std::unordered_set<ScheduleGraphNode *> &getIncomingArcs() const {
		return m_incoming_arc_s;
	}

private:
	vsc::IModelField									*m_action;
	int32_t												m_id;
	std::unordered_set<ScheduleGraphNode *>				m_incoming_arc_s;
	std::unordered_set<ScheduleGraphNode *>				m_outgoing_arc_s;
};

} /* namespace arl */

