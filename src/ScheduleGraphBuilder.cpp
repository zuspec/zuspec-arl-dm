/*
 * ScheduleGraphBuilder.cpp
 *
 *  Created on: May 7, 2022
 *      Author: mballance
 */

#include "ScheduleGraphBuilder.h"

namespace arl {

ScheduleGraphBuilder::ScheduleGraphBuilder() {
	// TODO Auto-generated constructor stub

}

ScheduleGraphBuilder::~ScheduleGraphBuilder() {
	// TODO Auto-generated destructor stub
}

void ScheduleGraphBuilder::build(
			std::vector<ScheduleGraphNodeUP>		&nodes,
			const std::vector<vsc::IModelField *>	&actions,
			const ScheduleSolveDataActionRel					&schedrel) {
	/*
	for (uint32_t i=0; i<actions.size(); i++) {
		nodes.push_back(ScheduleGraphNodeUP(
				new ScheduleGraphNode(actions.at(i), i)));
	}
	 */

	for (uint32_t i=0; i<actions.size(); i++) {
		for (uint32_t j=i+1; j<actions.size(); j++) {
			ScheduleRelE rel = schedrel.getRel(i, j);

			if (rel == ScheduleRelE::SeqAB) {
				nodes.at(i)->addOutgoingArc(nodes.at(j).get());
				nodes.at(j)->addIncomingArc(nodes.at(i).get());
			} else if (rel == ScheduleRelE::SeqBA) {
				nodes.at(j)->addOutgoingArc(nodes.at(i).get());
				nodes.at(i)->addIncomingArc(nodes.at(j).get());
			}
		}
	}
}

} /* namespace arl */
