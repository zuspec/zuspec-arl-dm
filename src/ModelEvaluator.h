/*
 * ModelEvaluator.h
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "arl/IModelEvaluator.h"

namespace arl {

class ModelEvaluator : public IModelEvaluator {
public:
	ModelEvaluator(IContext *ctxt);

	virtual ~ModelEvaluator();

	virtual IModelEvalIterator *eval(
			vsc::IModelField	*root_comp,
			IDataTypeAction		*root_action) override;

private:
	IContext					*m_ctxt;


};

} /* namespace arl */

