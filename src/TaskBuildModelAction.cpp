/*
 * TaskModelActionBuilder.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#include "TaskBuildModelAction.h"

namespace arl {

TaskBuildModelAction::TaskBuildModelAction(IContext *ctxt) :
		m_ctxt(ctxt), m_field_builder(ctxt, this) {

}

TaskBuildModelAction::~TaskBuildModelAction() {
	// TODO Auto-generated destructor stub
}

vsc::IModelField *TaskBuildModelAction::build(
		IDataTypeAction 	*t,
		const std::string 	&name) {
	return vsc::TaskBuildModelField(m_ctxt, this).build(t, name);
}

} /* namespace arl */
