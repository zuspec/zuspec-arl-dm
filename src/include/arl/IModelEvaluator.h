/*
 * IModelEvaluator.h
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelEvalIterator.h"
#include "vsc/IModelField.h"

namespace arl {

class IDataTypeAction;

class IModelEvaluator {
public:

	virtual ~IModelEvaluator() { }

	virtual IModelEvalIterator *eval(
			const vsc::IRandState	*randstate,
			vsc::IModelField		*root_comp,
			IDataTypeAction			*root_action) = 0;

};

}
