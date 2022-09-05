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

class IModelEvaluator {
public:

	virtual ~IModelEvaluator() { }

	virtual IModelEvalIterator *eval(
			const vsc::IRandState	*randstate,
			IModelFieldComponent	*root_comp,
			IDataTypeAction			*root_action) = 0;

};

}
