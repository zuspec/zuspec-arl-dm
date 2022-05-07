/*
 * ExecGraphBuilder.h
 *
 *  Created on: May 3, 2022
 *      Author: mballance
 */

#pragma once
#include <unordered_set>
#include "ExecGraphNode.h"
#include "ScheduleGraphNode.h"

namespace arl {

class ExecGraphBuilder {
public:
	ExecGraphBuilder();

	virtual ~ExecGraphBuilder();

	ExecGraphNode *build(const std::vector<ScheduleGraphNodeUP> &nodes);

protected:
	ScheduleGraphNode *processSequence(
			ExecGraphNode 		*parent,
			ScheduleGraphNode	*node);

	ScheduleGraphNode *processParallel(
			ExecGraphNode		*parent,
			ScheduleGraphNode	*node);

	void collectChildren(
			std::unordered_set<ScheduleGraphNode *> &nodes,
			ScheduleGraphNode						*node);

	ScheduleGraphNode *findCommonNode(
			const std::unordered_set<ScheduleGraphNode *> 	&nodes,
			ScheduleGraphNode								*node);

	void assignMaxDepth(ScheduleGraphNode *roots);

	void assignMaxDepth(int depth, ScheduleGraphNode *n);

	ScheduleGraphNode *processNodes(ScheduleGraphNode *start, ScheduleGraphNode *end);

private:
	std::vector<ExecGraphNode *>					m_exec_s;

};

} /* namespace arl */

