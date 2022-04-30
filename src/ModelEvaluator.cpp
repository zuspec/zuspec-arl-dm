/*
 * ModelEvaluator.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#include "ModelEvaluator.h"
#include "ModelEvalIterator.h"

namespace arl {

ModelEvaluator::ModelEvaluator(IContext *ctxt) : m_ctxt(ctxt) {
	// TODO Auto-generated constructor stub

}

ModelEvaluator::~ModelEvaluator() {
	// TODO Auto-generated destructor stub
}

IModelEvalIterator *ModelEvaluator::eval(
			vsc::IModelField	*root_comp,
			IDataTypeAction		*root_action) {
	vsc::IModelField *action = m_ctxt->buildModelAction(
			root_action,
			root_action->name());

	ModelEvalIterator *ret = new ModelEvalIterator({
		{
			ModelEvalNodeT::Action,
			{
					.action=action
			}
		}
	});

	return ret;
}

} /* namespace arl */
