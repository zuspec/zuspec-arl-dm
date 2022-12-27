/*
 * TaskBuildModelActivity.h
 *
 *  Created on: Jun 8, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "zsp/arl/dm/impl/VisitorBase.h"
#include "zsp/arl/dm/IModelActivity.h"
#include "zsp/arl/dm/IModelBuildContext.h"
#include "zsp/arl/dm/IDataTypeActivity.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/IModelField.h"

namespace zsp {
namespace arl {
namespace dm {


/**
 * This builder primarily links up the activity structure to
 * existing data models that are part of the action.
 */
class TaskBuildModelActivity : public VisitorBase {
public:
	TaskBuildModelActivity(IModelBuildContext *ctxt);

	virtual ~TaskBuildModelActivity();

	IModelActivity *build(ITypeFieldActivity *activity);

	virtual void visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) override;

	virtual void visitDataTypeActivitySequence(IDataTypeActivitySequence *t) override;

	virtual void visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) override;

	virtual void visitTypeFieldActivity(ITypeFieldActivity *f) override;

private:
	IModelBuildContext							*m_ctxt;
	std::vector<vsc::dm::ITypeField *>				m_field_s;
	std::vector<IModelActivityScope *>			m_scope_s;
	std::vector<vsc::dm::IModelField *>				m_ctxt_s;


};

}
}
}

