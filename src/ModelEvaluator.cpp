/*
 * ModelEvaluator.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#include "ModelEvaluator.h"
#include "ModelEvaluatorFullElab.h"
#include "ModelEvaluatorIncrElab.h"
#include "ModelEvaluatorThread.h"
#include "ModelActivityTraverse.h"
#include "TaskBuildModelAction.h"
#include "TaskCollectTopLevelActivities.h"

namespace arl {

ModelEvaluator::ModelEvaluator(
	IContext 			*ctxt,
	ModelEvaluatorKind	kind) : m_ctxt(ctxt) {
	switch (kind) {
		case ModelEvaluatorKind::FullElab:
			m_impl = IModelEvaluatorUP(new ModelEvaluatorFullElab(ctxt));
			break;
		case ModelEvaluatorKind::IncrElab:
			m_impl = IModelEvaluatorUP(new ModelEvaluatorIncrElab(ctxt));
			break;
	}
}

ModelEvaluator::~ModelEvaluator() {
	// TODO Auto-generated destructor stub
}

IModelEvalIterator *ModelEvaluator::eval(
			const vsc::IRandState		*randstate,
			IModelFieldComponent		*root_comp,
			IDataTypeAction				*root_action) {
	return m_impl->eval(randstate, root_comp, root_action);
}



} /* namespace arl */
