/*
 * ScheduleSolveProblem.cpp
 *
 *  Created on: May 21, 2022
 *      Author: mballance
 */

#include "ScheduleSolveProblem.h"

namespace arl {

ScheduleSolveProblem::ScheduleSolveProblem() {
	// TODO Auto-generated constructor stub

}

ScheduleSolveProblem::~ScheduleSolveProblem() {
	// TODO Auto-generated destructor stub
}

ScheduleSolveActionData *ScheduleSolveProblem::addActivity(
		IModelActivity *activity) {
	ScheduleSolveActionData *ret = new ScheduleSolveActionData(activity, false);

	m_actions.push_back(ScheduleSolveActionDataUP(ret));

	return ret;
}

} /* namespace arl */
