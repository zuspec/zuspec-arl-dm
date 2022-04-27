/*
 * TaskModelActionBuilder.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#include "TaskBuildModelAction.h"

namespace arl {

TaskBuildModelAction::TaskBuildModelAction(IContext *ctxt) : m_ctxt(ctxt) {
	// TODO Auto-generated constructor stub

}

TaskBuildModelAction::~TaskBuildModelAction() {
	// TODO Auto-generated destructor stub
}

vsc::IModelField *TaskBuildModelAction::build(
		IDataTypeAction 	*t,
		const std::string 	&name) {
	;
}

} /* namespace arl */
