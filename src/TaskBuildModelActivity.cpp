/*
 * TaskBuildModelActivity.cpp
 *
 *  Created on: Jun 8, 2022
 *      Author: mballance
 */

#include "TaskBuildModelActivity.h"
#include "ModelActivityTraverse.h"

namespace arl {

TaskBuildModelActivity::TaskBuildModelActivity(
		vsc::IModelBuildContext *ctxt) : m_ctxt(ctxt) {
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

void TaskBuildModelActivity::visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) {

}

void TaskBuildModelActivity::visitDataTypeActivitySequence(IDataTypeActivitySequence *t) {

}

void TaskBuildModelActivity::visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) {
	/*
	ModelActivityTraverse *traverse = new ModelActivityTraverse(
			target,
			with_c);
	 */

}

} /* namespace arl */
