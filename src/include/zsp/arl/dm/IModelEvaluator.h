/*
 * IModelEvaluator.h
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelEvalIterator.h"
#include "arl/IModelFieldComponent.h"
#include "vsc/IModelField.h"

namespace arl {

class IDataTypeAction;

enum class ModelEvaluatorKind {
	FullElab,
	IncrElab
};

class IModelEvaluator;
using IModelEvaluatorUP=std::unique_ptr<IModelEvaluator>;
class IModelEvaluator {
public:

	virtual ~IModelEvaluator() { }

	virtual IModelEvalIterator *eval(
			const vsc::IRandState	*randstate,
			IModelFieldComponent	*root_comp,
			IDataTypeAction			*root_action) = 0;

};

}
