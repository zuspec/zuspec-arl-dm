/*
 * TaskBuildModelActivity.h
 *
 *  Created on: Jun 8, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/impl/VisitorBase.h"
#include "arl/IModelActivity.h"
#include "arl/IModelBuildContext.h"
#include "arl/IDataTypeActivity.h"
#include "vsc/IModelBuildContext.h"
#include "vsc/IModelField.h"

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
	std::vector<vsc::ITypeField *>				m_field_s;
	std::vector<IModelActivityScope *>			m_scope_s;
	std::vector<vsc::IModelField *>				m_ctxt_s;


};

}
}
}

