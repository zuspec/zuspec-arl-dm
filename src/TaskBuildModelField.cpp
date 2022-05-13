/*
 * TaskBuildModelField.cpp
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#include "TaskBuildModelField.h"

namespace arl {

TaskBuildModelField::TaskBuildModelField(IContext *ctxt) :
	VisitorDelegator(&m_core), m_ctxt(ctxt), m_core(ctxt, this) {
	// TODO Auto-generated constructor stub

}

TaskBuildModelField::~TaskBuildModelField() {
	// TODO Auto-generated destructor stub
}

vsc::IModelField *TaskBuildModelField::build(vsc::IDataTypeStruct *type, const std::string &name) {
	return m_core.build(type, name);
}

} /* namespace arl */
