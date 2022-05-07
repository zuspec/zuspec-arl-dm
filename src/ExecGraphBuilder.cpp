/*
 * ExecGraphBuilder.cpp
 *
 *  Created on: May 3, 2022
 *      Author: mballance
 */

#include <stdio.h>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "ExecGraphBuilder.h"

#define DEBUG(fmt, ...) \
	fprintf(stdout, "ExecGraphBuilder: "); \
	fprintf(stdout, fmt, ##__VA_ARGS__); \
	fprintf(stdout, "\n")
#define DEBUG_ENTER(fmt, ...) \
	fprintf(stdout, "--> ExecGraphBuilder::"); \
	fprintf(stdout, fmt, ##__VA_ARGS__); \
	fprintf(stdout, "\n")
#define DEBUG_LEAVE(fmt, ...) \
	fprintf(stdout, "<-- ExecGraphBuilder::"); \
	fprintf(stdout, fmt, ##__VA_ARGS__); \
	fprintf(stdout, "\n")

namespace arl {

ExecGraphBuilder::ExecGraphBuilder() {
	// TODO Auto-generated constructor stub

}

ExecGraphBuilder::~ExecGraphBuilder() {
	// TODO Auto-generated destructor stub
}

ExecGraphNode *ExecGraphBuilder::build(
		const std::vector<ScheduleGraphNodeUP> &nodes) {
	ScheduleGraphNode roots(0, -1);

	// Root is always a sequence
	ExecGraphNode *root = new ExecGraphNode(ExecGraphNodeKindE::Sequence);
	m_exec_s.push_back(root);

	// First, find all nodes without an inbound arc
	for (auto it=nodes.begin(); it!=nodes.end(); it++) {
		if ((*it)->getIncomingArcs().size() == 0) {
			roots.addOutgoingArc(it->get());
		}
	}

	ScheduleGraphNode *node = &roots;

	assignMaxDepth(node);

	while (node) {
		if (node->getOutgoingArcs().size() == 1) {
			// Starts with a sequence
			fprintf(stdout, "sequence\n");
			if (node == &roots) {
				node = processSequence(
						root,
						*node->getOutgoingArcs().begin());
			} else {
				node = processSequence(root, node);
			}
		} else {
			// Starts with a parallel
			node = processParallel(
					root,
					node);
			fprintf(stdout, "parallel\n");
			node = 0;
		}
	}
	m_exec_s.pop_back();

	return root;
}

ScheduleGraphNode *ExecGraphBuilder::processSequence(
			ExecGraphNode 		*parent,
			ScheduleGraphNode	*node) {
	bool new_seq = false;
	if (m_exec_s.back()->kind() != ExecGraphNodeKindE::Sequence) {
		ExecGraphNode *scope = new ExecGraphNode(ExecGraphNodeKindE::Sequence);
		m_exec_s.back()->addChild(scope);
		m_exec_s.push_back(scope);
		new_seq = true;
	}

	while (node && node->getOutgoingArcs().size() <= 1) {
		m_exec_s.back()->addChild(new ExecGraphNode(
				ExecGraphNodeKindE::Traverse,
				node->action()));
		if (node->getOutgoingArcs().size() == 0) {
			node = 0;
		} else if (node->getOutgoingArcs().size() == 1) {
			node = *node->getOutgoingArcs().begin();
		}
	}

	if (new_seq) {
		m_exec_s.pop_back();
	}

	return node;
}

ScheduleGraphNode *ExecGraphBuilder::processParallel(
			ExecGraphNode 		*parent,
			ScheduleGraphNode	*node) {
	// The parallel branch happens after 'node'
	m_exec_s.back()->addChild(new ExecGraphNode(ExecGraphNodeKindE::Traverse, 0));

	int32_t i=0;
	/**
	 * Tuple is: <End, StartI, StartJ>
	 */
	using BranchSetT=std::tuple<ScheduleGraphNode *, ScheduleGraphNode *, ScheduleGraphNode *>;
	std::vector<BranchSetT> branches;
	for (auto it_i=node->getOutgoingArcs().begin();
			it_i!=node->getOutgoingArcs().end(); it_i++) {
		std::unordered_set<ScheduleGraphNode *> nodes;

		// Collect nodes on this branch
		collectChildren(nodes, *it_i);

		auto it_j_init = it_i;
		it_j_init++;
		int32_t j=i+1;
		for (auto it_j=it_j_init; it_j!=node->getOutgoingArcs().end(); it_j++) {
			// See where the paired branch ends with respect to the first branch
			ScheduleGraphNode *ret = findCommonNode(nodes, *it_j);

			// Note: a well-formed graph always has join points

			branches.push_back({ret, *it_i, *it_j});

			fprintf(stdout, "[%d,%d] findCommonNode: %p %d %d\n",
					(*it_i)->id(), (*it_j)->id(), ret, ret->id(), ret->getDepth());
			j++;
		}
		i++;
	}

	std::sort(branches.begin(), branches.end(), [&](const BranchSetT &b1, const BranchSetT &b2) {
		return std::get<0>(b1)->getDepth() < std::get<0>(b2)->getDepth();});
	std::unordered_set<ScheduleGraphNode *> taken_start_nodes;
	/**
	 * Map from end-node to set of start nodes
	 */
	using JoinForkT=std::unordered_map<ScheduleGraphNode *, std::vector<ScheduleGraphNode *>>;
	JoinForkT join_fork_m;

	std::vector<ScheduleGraphNode *> end_nodes;
	for (auto it=branches.begin(); it!=branches.end(); it++) {
		fprintf(stdout, "%d (%d): %d,%d\n",
				std::get<0>(*it)->getDepth(),
				std::get<0>(*it)->id(),
				std::get<1>(*it)->id(),
				std::get<2>(*it)->id());
		if (taken_start_nodes.find(std::get<1>(*it)) == taken_start_nodes.end()) {
			fprintf(stdout, "  claiming start-node %d\n", std::get<1>(*it)->id());
			taken_start_nodes.insert(std::get<1>(*it));

			// Add an entry for the end node if it doesn't exist
			JoinForkT::iterator jfm_it = join_fork_m.find(std::get<0>(*it));
			if (jfm_it == join_fork_m.end()) {
				jfm_it=join_fork_m.insert({std::get<0>(*it), {}}).first;
				end_nodes.push_back(std::get<0>(*it));
			}
			// Add the start point
			jfm_it->second.push_back(std::get<1>(*it));

		} else {
			fprintf(stdout, "  ignoring start-node %d\n", std::get<1>(*it)->id());
		}

		if (taken_start_nodes.find(std::get<2>(*it)) == taken_start_nodes.end()) {
			fprintf(stdout, "  claiming start-node %d\n", std::get<2>(*it)->id());
			taken_start_nodes.insert(std::get<2>(*it));

			// Add an entry for the end node if it doesn't exist
			JoinForkT::iterator jfm_it = join_fork_m.find(std::get<0>(*it));
			if (jfm_it == join_fork_m.end()) {
				jfm_it=join_fork_m.insert({std::get<0>(*it), {}}).first;
				end_nodes.push_back(std::get<0>(*it));
			}
			// Add the start point
			jfm_it->second.push_back(std::get<2>(*it));
		} else {
			fprintf(stdout, "  ignoring start-node %d\n", std::get<2>(*it)->id());
		}
	}

	for (auto it=join_fork_m.begin(); it!=join_fork_m.end(); it++) {
		fprintf(stdout, "End-point: %d\n", it->first->id());
		for (auto it_s=it->second.begin(); it_s!=it->second.end(); it_s++) {
			fprintf(stdout, "  Start: %d\n", (*it_s)->id());
		}
	}

	for (auto it=end_nodes.begin(); it!=end_nodes.end(); it++) {
		ExecGraphNode *fork_join = new ExecGraphNode(ExecGraphNodeKindE::Parallel);

		if (it != end_nodes.begin()) {
			// Grab previous scope and add to ours
			fork_join->addChild(m_exec_s.back());
			m_exec_s.pop_back();
		}
		m_exec_s.push_back(fork_join);

		// Process the start nodes
		JoinForkT::const_iterator b_it=join_fork_m.find(*it);
		ScheduleGraphNode *end = b_it->first;

		for (auto b=b_it->second.begin(); b!=b_it->second.end(); b++) {
			ExecGraphNode *branch = new ExecGraphNode(ExecGraphNodeKindE::Sequence);
			m_exec_s.push_back(branch);

			ScheduleGraphNode *next = processNodes(*b, end);

			m_exec_s.pop_back();

//			// Add the end-node
//			// TODO: need to be a bit smarter here...
//			m_exec_s.back()->addChild(new ExecGraphNode(ExecGraphNodeKindE::Traverse, 0));

			fork_join->addChild(branch);
		}

		if (it+1 != end_nodes.end()) {
			// Replace the fork_join with a sequence that includes the end node
			ExecGraphNode *seq = new ExecGraphNode(ExecGraphNodeKindE::Sequence);
			seq->addChild(m_exec_s.back());
			m_exec_s.pop_back();
			seq->addChild(new ExecGraphNode(ExecGraphNodeKindE::Traverse, 0));
			m_exec_s.push_back(seq);
		} else {
			// If we are at the end, add the last fork/join to the parent
			// scope and the terminating node after
			ExecGraphNode *last_fork_join = m_exec_s.back();
			m_exec_s.pop_back();
			m_exec_s.back()->addChild(last_fork_join);
			m_exec_s.back()->addChild(new ExecGraphNode(ExecGraphNodeKindE::Traverse, 0));
		}
	}

	// But, then we want to traverse the nodes starting with the
	// first-to-end nodes

	return 0;
}

ScheduleGraphNode *ExecGraphBuilder::processNodes(
		ScheduleGraphNode *start,
		ScheduleGraphNode *end) {
	DEBUG_ENTER("processNodes %d %d", start->id(), end->id());
	ScheduleGraphNode *node = start;

	// Process sequential nodes
	while (node != end) {
		if (node->getOutgoingArcs().size() > 1) {
			node = processParallel(0, node);
		} else {
			m_exec_s.back()->addChild(new ExecGraphNode(node->action()));
			node = (*node->getOutgoingArcs().begin());
		}
	}

	DEBUG_LEAVE("processNodes %d %d -> %d", start->id(), end->id(), node->id());
	return node;
}


void ExecGraphBuilder::collectChildren(
			std::unordered_set<ScheduleGraphNode *>	&nodes,
			ScheduleGraphNode						*node) {
	std::unordered_set<ScheduleGraphNode *>::const_iterator it;

	if ((it=nodes.find(node)) == nodes.end()) {
		nodes.insert(node);
	} else {
		// Once we've hit a duplicate node, we can stop searching
		return;
	}

	for (auto it=node->getOutgoingArcs().begin();
			it!=node->getOutgoingArcs().end(); it++) {
		collectChildren(nodes, *it);
	}
}

ScheduleGraphNode *ExecGraphBuilder::findCommonNode(
			const std::unordered_set<ScheduleGraphNode *> 	&nodes,
			ScheduleGraphNode								*node) {
	ScheduleGraphNode *ret = 0;
	std::unordered_set<ScheduleGraphNode *>::const_iterator n_it;

	for (auto it=node->getOutgoingArcs().begin();
			it!=node->getOutgoingArcs().end(); it++) {
		if (nodes.find(*it) != nodes.end()) {
			fprintf(stdout, "Found with depth %d\n", (*it)->getDepth());
			ret = *it;
			break;
		} else if ((ret=findCommonNode(nodes, *it))) {
			break;
		}
	}

	return ret;
}

void ExecGraphBuilder::assignMaxDepth(ScheduleGraphNode *roots) {
	for (auto it=roots->getOutgoingArcs().begin();
			it!=roots->getOutgoingArcs().end(); it++) {
		assignMaxDepth(0, *it);
	}
}

void ExecGraphBuilder::assignMaxDepth(int depth, ScheduleGraphNode *n) {
	if (depth > n->getDepth()) {
		n->setDepth(depth);
	}

	for (auto it=n->getOutgoingArcs().begin();
			it!=n->getOutgoingArcs().end(); it++) {
		assignMaxDepth(depth+1, *it);
	}
}


} /* namespace arl */
