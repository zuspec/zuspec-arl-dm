/*
 * TestBuildModelComponent.h
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IContext.h"
#include "include/arl/impl/VisitorBase.h"
#include "include/arl/impl/VisitorDelegator.h"
#include "vsc/IModelField.h"
#include "vsc/impl/TaskBuildModelField.h"

namespace arl {

class TaskBuildModelComponent : public VisitorDelegator {
public:
	TaskBuildModelComponent(IContext *ctxt);

	virtual ~TaskBuildModelComponent();

	vsc::IModelField *build(arl::IDataTypeComponent *c, const std::string &name);

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override;

	virtual void visitTypeFieldPool(ITypeFieldPool *f) override;

private:
	IContext							*m_ctxt;
	std::vector<vsc::IModelField *>		m_field_s;
	vsc::TaskBuildModelField			m_core;

};

} /* namespace arl */

