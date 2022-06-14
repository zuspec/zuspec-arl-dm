/*
 * TaskModelActionBuilder.h
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelBuildContext.h"
#include "arl/IModelFieldAction.h"
#include "include/arl/impl/VisitorDelegator.h"
#include "vsc/IModelField.h"
#include "vsc/IModelBuildContext.h"
#include "vsc/impl/TaskBuildModelField.h"

namespace arl {

class TaskBuildModelAction : public VisitorDelegator {
public:
	TaskBuildModelAction(IModelBuildContext *ctxt);

	virtual ~TaskBuildModelAction();

	IModelFieldAction *build(IDataTypeAction *t, const std::string &name);

	virtual void visitDataTypeAction(IDataTypeAction *t) override;

private:
	IModelBuildContext			*m_ctxt;
	vsc::TaskBuildModelField	m_core;

};

} /* namespace arl */

