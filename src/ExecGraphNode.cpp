/*
 * ExecGraphNode.cpp
 *
 *  Created on: May 2, 2022
 *      Author: mballance
 */

#include "ExecGraphNode.h"

namespace arl {

ExecGraphNode::ExecGraphNode(ExecGraphNodeKindE kind) : m_kind(kind), m_action(0) {

}

ExecGraphNode::ExecGraphNode(ExecGraphNodeKindE kind, vsc::IModelField *action) :
		m_kind(kind), m_action(action) {

}

ExecGraphNode::~ExecGraphNode() {
	// TODO Auto-generated destructor stub
}

} /* namespace arl */
