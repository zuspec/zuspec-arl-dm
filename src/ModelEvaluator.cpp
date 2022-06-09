/*
 * ModelEvaluator.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#include "ModelEvaluator.h"
#include "ModelEvalIteratorMgr.h"

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
	IModelFieldAction *action = m_ctxt->buildModelAction(
			root_action,
			root_action->name());

	// Need to do initial setup work to create list of
	// top-level activities to solve

	return new ModelEvalIteratorMgr(this);
}

IModelEvalIterator *ModelEvaluator::next() {
	// Time to determine what to do next at the top level

	return 0;
}

} /* namespace arl */
