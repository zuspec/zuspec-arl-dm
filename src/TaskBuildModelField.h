/*
 * TaskBuildModelField.h
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "include/arl/impl/VisitorDelegator.h"
#include "vsc/IModelBuildContext.h"
#include "vsc/IModelField.h"
#include "vsc/impl/TaskBuildModelField.h"

namespace arl {

class TaskBuildModelField : public VisitorDelegator {
public:
	TaskBuildModelField(vsc::IModelBuildContext *ctxt);

	virtual ~TaskBuildModelField();

	virtual vsc::IModelField *build(
		vsc::IDataTypeStruct *type, 
		const std::string &name);

private:
	vsc::IModelBuildContext		*m_ctxt;
	vsc::TaskBuildModelField	m_core;
};

} /* namespace arl */

