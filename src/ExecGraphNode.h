/*
 * ExecGraphNode.h
 *
 *  Created on: May 2, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
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

	ExecGraphNode(vsc::IModelField *action);

	ExecGraphNode(ExecGraphNodeKindE kind, vsc::IModelField *action);

	virtual ~ExecGraphNode();

	const ExecGraphNodeKindE kind() const { return m_kind; }

	vsc::IModelField *action() const { return m_action; }

	void addChild(ExecGraphNode *c) {
		m_children.push_back(ExecGraphNodeUP(c));
	}

	const std::vector<ExecGraphNodeUP> &children() const { return m_children; }

	std::vector<ExecGraphNodeUP> &children() { return m_children; }

protected:
	ExecGraphNodeKindE				m_kind;
	vsc::IModelField				*m_action;
	std::vector<ExecGraphNodeUP>	m_children;
};

} /* namespace arl */

