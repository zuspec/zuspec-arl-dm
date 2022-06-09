/*
 * TaskBuildModelActivity.cpp
 *
 *  Created on: Jun 8, 2022
 *      Author: mballance
 */

#include "TaskBuildModelActivity.h"

namespace arl {

TaskBuildModelActivity::TaskBuildModelActivity() {
	// TODO Auto-generated constructor stub

}

TaskBuildModelActivity::~TaskBuildModelActivity() {
	// TODO Auto-generated destructor stub
}

IModelActivity *TaskBuildModelActivity::build(
			vsc::IModelField	*parent_ctxt,
			IDataTypeActivity	*activity) {
	m_ctxt_s.push_back(parent_ctxt);
	activity->accept(m_this);

	return 0;
}

void TaskBuildModelActivity::visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) { }

void TaskBuildModelActivity::visitDataTypeActivitySequence(IDataTypeActivitySequence *t) { }

void TaskBuildModelActivity::visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) { }

} /* namespace arl */
