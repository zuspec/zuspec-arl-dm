/*
 * ScheduleSolveActionData.cpp
 *
 *  Created on: May 21, 2022
 *      Author: mballance
 */

#include "ScheduleSolveActionData.h"

namespace arl {

ScheduleSolveActionData::ScheduleSolveActionData(
		vsc::IModelField			*action,
		bool						owned) : m_action(action), m_owned(owned) {

}

ScheduleSolveActionData::~ScheduleSolveActionData() {
	if (m_owned && m_action) {
		delete m_action;
	}
}

} /* namespace arl */
