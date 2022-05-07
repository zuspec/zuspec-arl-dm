/*
 * ExecGraphNode.cpp
 *
 *  Created on: May 2, 2022
 *      Author: mballance
 */

#include "ExecGraphNode.h"
#include "ExecGraph2String.h"

namespace arl {

ExecGraphNode::ExecGraphNode(ExecGraphNodeKindE kind) : m_kind(kind), m_action(0) {

}

ExecGraphNode::ExecGraphNode(vsc::IModelField *action) :
		m_kind(ExecGraphNodeKindE::Traverse), m_action(action) {

}

ExecGraphNode::ExecGraphNode(ExecGraphNodeKindE kind, vsc::IModelField *action) :
		m_kind(kind), m_action(action) {

}

ExecGraphNode::~ExecGraphNode() {
	// TODO Auto-generated destructor stub
}

std::string ExecGraphNode::toString() {
	return ExecGraph2String().toString(this);
}

} /* namespace arl */
