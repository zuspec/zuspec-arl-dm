/*
 * TaskBuildModelField.h
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/impl/VisitorDelegator.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/IModelField.h"
#include "vsc/dm/impl/TaskBuildModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class TaskBuildModelField : public VisitorDelegator {
public:
	TaskBuildModelField(vsc::dm::IModelBuildContext *ctxt);

	virtual ~TaskBuildModelField();

	virtual vsc::dm::IModelField *build(
		vsc::dm::IDataTypeStruct *type, 
		const std::string &name);

private:
	vsc::dm::IModelBuildContext		*m_ctxt;
	vsc::dm::TaskBuildModelField	m_core;
};

}
}
}

