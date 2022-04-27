/*
 * TestBuildModelComponent.h
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IContext.h"
#include "arl/VisitorBase.h"
#include "vsc/IModelField.h"

namespace arl {

class TaskBuildModelComponent : public VisitorBase {
public:
	TaskBuildModelComponent(IContext *ctxt);

	virtual ~TaskBuildModelComponent();

	vsc::IModelField *build(arl::IDataTypeComponent *c, const std::string &name);

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override;

private:
	IContext							*m_ctxt;
	std::vector<vsc::IModelField *>		m_field_s;

};

} /* namespace arl */

