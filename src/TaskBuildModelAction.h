/*
 * TaskModelActionBuilder.h
 *
 *  Created on: Apr 26, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IModelBuildContext.h"
#include "zsp/arl/dm/IModelFieldAction.h"
#include "zsp/arl/dm/impl/VisitorDelegator.h"
#include "vsc/dm/IModelField.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/impl/TaskBuildModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class TaskBuildModelAction : public VisitorDelegator {
public:
	TaskBuildModelAction(IModelBuildContext *ctxt);

	virtual ~TaskBuildModelAction();

	IModelFieldAction *build(IDataTypeAction *t, const std::string &name);

	virtual void visitDataTypeAction(IDataTypeAction *t) override;

	virtual void visitTypeFieldActivity(ITypeFieldActivity *f) override;

	virtual void visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) override;

	virtual void visitDataTypeActivitySequence(IDataTypeActivitySequence *t) override;

	virtual void visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) override;

private:
	IModelBuildContext						*m_ctxt;
	vsc::dm::TaskBuildModelField				m_core;
	std::vector<ITypeFieldActivity *>		m_activity_s;

};

}
}
}

