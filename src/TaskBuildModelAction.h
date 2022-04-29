/*
 * TaskModelActionBuilder.h
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "include/arl/impl/VisitorBase.h"
#include "vsc/IModelField.h"
#include "vsc/impl/TaskBuildModelField.h"

namespace arl {

class TaskBuildModelAction : public VisitorBase {
public:
	TaskBuildModelAction(IContext *ctxt);

	virtual ~TaskBuildModelAction();

	vsc::IModelField *build(IDataTypeAction *t, const std::string &name);

private:
	IContext					*m_ctxt;
	vsc::TaskBuildModelField	m_field_builder;

};

} /* namespace arl */

