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
#include "arl/IModelFieldComponent.h"

namespace arl {

class ModelEvaluator : public IModelEvaluator, public VisitorBase {
public:
	ModelEvaluator(
		IContext 				*ctxt,
		ModelEvaluatorKind		kind);

	virtual ~ModelEvaluator();

	virtual IModelEvalIterator *eval(
			const vsc::IRandState	*randstate,
			IModelFieldComponent	*root_comp,
			IDataTypeAction			*root_action) override;

private:
	IContext						*m_ctxt;
	IModelEvaluatorUP				m_impl;




};

} /* namespace arl */

