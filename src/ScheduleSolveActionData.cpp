/*
 * ScheduleSolveActionData.cpp
 *
 *  Created on: May 21, 2022
 *      Author: mballance
 */

#include "ScheduleSolveActionData.h"

namespace arl {

ScheduleSolveActionData::ScheduleSolveActionData(
		IModelActivity				*activity,
		bool						owned) : m_activity(activity), m_owned(owned),
				m_node(new ScheduleGraphNode(activity, 0)) {

}

ScheduleSolveActionData::~ScheduleSolveActionData() {
	if (m_owned && m_activity) {
		delete m_activity;
	}
}

} /* namespace arl */
