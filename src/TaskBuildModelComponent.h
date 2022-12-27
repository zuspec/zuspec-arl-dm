/*
 * TestBuildModelComponent.h
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "zsp/arl/dm/IModelBuildContext.h"
#include "zsp/arl/dm/impl/VisitorBase.h"
#include "zsp/arl/dm/impl/VisitorDelegator.h"
#include "vsc/dm/IModelField.h"
#include "vsc/dm/impl/TaskBuildModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class TaskBuildModelComponent : public VisitorDelegator {
public:
	TaskBuildModelComponent(IModelBuildContext *ctxt);

	virtual ~TaskBuildModelComponent();

	IModelFieldComponent *build(arl::dm::IDataTypeComponent *c, const std::string &name);

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override;

	virtual void visitTypeFieldPool(ITypeFieldPool *f) override;

private:
	IModelBuildContext					*m_ctxt;
	std::vector<vsc::dm::IModelField *>		m_field_s;
	vsc::dm::TaskBuildModelField			m_core;

};

}
}
}

