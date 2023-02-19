/*
 * IModelEvaluator.h
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IModelEvalIterator.h"
#include "zsp/arl/dm/IModelFieldComponent.h"
#include "vsc/dm/IModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeAction;

enum class ModelEvaluatorKind {
	FullElab,
	IncrElab
};

class IModelEvaluator;
using IModelEvaluatorUP=vsc::dm::UP<IModelEvaluator>;
class IModelEvaluator {
public:

	virtual ~IModelEvaluator() { }

	virtual IModelEvalIterator *eval(
			const vsc::dm::IRandState	*randstate,
			IModelFieldComponent	*root_comp,
			IDataTypeAction			*root_action) = 0;

};

}
}
}
