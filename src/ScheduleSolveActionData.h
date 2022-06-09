/*
 * ScheduleSolveActionData.h
 *
 *  Created on: May 21, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "arl/IModelActivity.h"
#include "vsc/IModelField.h"
#include "ScheduleGraphNode.h"

namespace arl {

class ScheduleSolveActionData;
using ScheduleSolveActionDataUP=std::unique_ptr<ScheduleSolveActionData>;
class ScheduleSolveActionData {
public:
	ScheduleSolveActionData(
			IModelActivity			*activity,
			bool					owned
			);

	virtual ~ScheduleSolveActionData();

	ScheduleGraphNode *node() const { return m_node.get(); }

private:
	IModelActivity				*m_activity;
	bool						m_owned;
	ScheduleGraphNodeUP			m_node;

};

} /* namespace arl */

