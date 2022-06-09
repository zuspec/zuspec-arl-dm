/*
 * ExecGraphNode.cpp
 *
 *  Created on: May 2, 2022
 *      Author: mballance
 */

#include "ExecGraphNode.h"
#include "ExecGraph2String.h"

namespace arl {

ExecGraphNode::ExecGraphNode(ExecGraphNodeKindE kind) : m_kind(kind), m_activity(0) {

}

ExecGraphNode::ExecGraphNode(IModelActivity *activity) :
		m_kind(ExecGraphNodeKindE::Traverse), m_activity(activity) {

}

ExecGraphNode::ExecGraphNode(ExecGraphNodeKindE kind, IModelActivity *activity) :
		m_kind(kind), m_activity(activity) {

}

ExecGraphNode::~ExecGraphNode() {
	// TODO Auto-generated destructor stub
}

std::string ExecGraphNode::toString() {
	return ExecGraph2String().toString(this);
}

} /* namespace arl */
