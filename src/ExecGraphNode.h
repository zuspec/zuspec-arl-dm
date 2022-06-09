/*
 * ExecGraphNode.h
 *
 *  Created on: May 2, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "arl/IModelActivity.h"
#include "vsc/IModelField.h"

namespace arl {

enum class ExecGraphNodeKindE {
	Sequence,
	Parallel,
	Traverse
};

class ExecGraphNode;
using ExecGraphNodeUP=std::unique_ptr<ExecGraphNode>;
class ExecGraphNode {
public:

	ExecGraphNode(ExecGraphNodeKindE kind);

	ExecGraphNode(IModelActivity *activity);

	ExecGraphNode(ExecGraphNodeKindE kind, IModelActivity *activity);

	virtual ~ExecGraphNode();

	const ExecGraphNodeKindE kind() const { return m_kind; }

	IModelActivity *activity() const { return m_activity; }

	void addChild(ExecGraphNode *c) {
		m_children.push_back(ExecGraphNodeUP(c));
	}

	const std::vector<ExecGraphNodeUP> &children() const { return m_children; }

	std::vector<ExecGraphNodeUP> &children() { return m_children; }

	std::string toString();

protected:
	ExecGraphNodeKindE				m_kind;
	IModelActivity					*m_activity;
	std::vector<ExecGraphNodeUP>	m_children;
};

} /* namespace arl */

