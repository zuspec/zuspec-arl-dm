/*
 * ModelEvaluator.h
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/impl/VisitorBase.h"
#include "arl/IContext.h"
#include "arl/IModelActivity.h"
#include "arl/IModelEvaluator.h"

namespace arl {

class ModelEvaluator : public IModelEvaluator, public VisitorBase {
public:
	ModelEvaluator(IContext *ctxt);

	virtual ~ModelEvaluator();

	virtual IModelEvalIterator *eval(
			const vsc::IRandState	*randstate,
			vsc::IModelField		*root_comp,
			IDataTypeAction			*root_action) override;

	virtual IModelEvalIterator *next();

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

private:
	IContext						*m_ctxt;
	vsc::IRandStateUP				m_randstate;
	IModelFieldActionUP				m_action;
	IModelActivityTraverseUP		m_dummy_activity;
	uint32_t						m_activity_idx;
	std::vector<IModelActivity *>	m_activities;
	IModelEvalIterator				*m_next;


};

} /* namespace arl */

