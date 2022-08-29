/*
 * TestBuildModelComponent.h
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IModelBuildContext.h"
#include "include/arl/impl/VisitorBase.h"
#include "include/arl/impl/VisitorDelegator.h"
#include "vsc/IModelField.h"
#include "vsc/impl/TaskBuildModelField.h"

namespace arl {

class TaskBuildModelComponent : public VisitorDelegator {
public:
	TaskBuildModelComponent(IModelBuildContext *ctxt);

	virtual ~TaskBuildModelComponent();

	IModelFieldComponent *build(arl::IDataTypeComponent *c, const std::string &name);

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override;

	virtual void visitTypeFieldPool(ITypeFieldPool *f) override;

private:
	IModelBuildContext					*m_ctxt;
	std::vector<vsc::IModelField *>		m_field_s;
	vsc::TaskBuildModelField			m_core;

};

} /* namespace arl */

