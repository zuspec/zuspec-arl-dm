/*
 * TestScheduleGraphNode.cpp
 *
 *  Created on: May 3, 2022
 *      Author: mballance
 */

#include "ExecGraphBuilder.h"
#include "ScheduleGraphNode.h"
#include "ScheduleGraphArcTrimmer.h"
#include "TestScheduleGraphNode.h"

namespace arl {

TestScheduleGraphNode::TestScheduleGraphNode() {
	// TODO Auto-generated constructor stub

}

TestScheduleGraphNode::~TestScheduleGraphNode() {
	// TODO Auto-generated destructor stub
}

TEST_F(TestScheduleGraphNode, test_smoke) {
	std::vector<ScheduleGraphNodeUP> nodes(6);
	for (uint32_t i=0; i<nodes.size(); i++) {
		nodes[i] = ScheduleGraphNodeUP(new ScheduleGraphNode(0, i));
	}

	// nodes[4]
	// nodes[3] nodes[2] nodes[5]
	// nodes[1]
	// nodes[0]

	nodes[4]->addOutgoingArc(nodes[3].get());
	nodes[3]->addIncomingArc(nodes[4].get());
	nodes[4]->addOutgoingArc(nodes[2].get());
	nodes[2]->addIncomingArc(nodes[4].get());
	nodes[4]->addOutgoingArc(nodes[5].get());
	nodes[5]->addIncomingArc(nodes[4].get());

	// Redundant arcs from 4->1 and 4->0
	nodes[4]->addOutgoingArc(nodes[1].get());
	nodes[1]->addIncomingArc(nodes[4].get());
	nodes[4]->addOutgoingArc(nodes[0].get());
	nodes[0]->addIncomingArc(nodes[4].get());

	nodes[3]->addOutgoingArc(nodes[1].get());
	nodes[1]->addIncomingArc(nodes[3].get());
	nodes[2]->addOutgoingArc(nodes[1].get());
	nodes[1]->addIncomingArc(nodes[2].get());
	nodes[5]->addOutgoingArc(nodes[0].get());
	nodes[0]->addIncomingArc(nodes[5].get());

	// Redundant arcs from 3->0 and 2->0
	nodes[3]->addOutgoingArc(nodes[0].get());
	nodes[0]->addIncomingArc(nodes[3].get());
	nodes[2]->addOutgoingArc(nodes[0].get());
	nodes[0]->addIncomingArc(nodes[2].get());

	nodes[1]->addOutgoingArc(nodes[0].get());
	nodes[0]->addIncomingArc(nodes[1].get());

	for (uint32_t i=0; i<nodes.size(); i++) {
		fprintf(stdout, "Node %d\n", nodes.at(i)->id());
		fprintf(stdout, "  Outgoing: ");
		for (auto it=nodes.at(i)->getOutgoingArcs().begin();
				it!=nodes.at(i)->getOutgoingArcs().end(); it++) {
			if (it != nodes.at(i)->getOutgoingArcs().begin()) {
				fprintf(stdout, ", ");
			}
			fprintf(stdout, "%d", (*it)->id());
		}
		fprintf(stdout, "\n");
		fprintf(stdout, "  Incoming: ");
		for (auto it=nodes.at(i)->getIncomingArcs().begin();
				it!=nodes.at(i)->getIncomingArcs().end(); it++) {
			if (it != nodes.at(i)->getIncomingArcs().begin()) {
				fprintf(stdout, ", ");
			}
			fprintf(stdout, "%d", (*it)->id());
		}
		fprintf(stdout, "\n");
	}

	ScheduleGraphArcTrimmer().trim(nodes);

	for (uint32_t i=0; i<nodes.size(); i++) {
		fprintf(stdout, "Node %d\n", nodes.at(i)->id());
		fprintf(stdout, "  Outgoing: ");
		for (auto it=nodes.at(i)->getOutgoingArcs().begin();
				it!=nodes.at(i)->getOutgoingArcs().end(); it++) {
			if (it != nodes.at(i)->getOutgoingArcs().begin()) {
				fprintf(stdout, ", ");
			}
			fprintf(stdout, "%d", (*it)->id());
		}
		fprintf(stdout, "\n");
		fprintf(stdout, "  Incoming: ");
		for (auto it=nodes.at(i)->getIncomingArcs().begin();
				it!=nodes.at(i)->getIncomingArcs().end(); it++) {
			if (it != nodes.at(i)->getIncomingArcs().begin()) {
				fprintf(stdout, ", ");
			}
			fprintf(stdout, "%d", (*it)->id());
		}
		fprintf(stdout, "\n");
	}

	ExecGraphBuilder().build(nodes);
}

} /* namespace arl */
