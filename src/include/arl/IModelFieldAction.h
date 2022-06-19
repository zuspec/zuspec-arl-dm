/*
 * IModelFieldAction.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelActivityScope.h"
#include "vsc/IModelField.h"

namespace arl {

class IModelFieldAction;
using IModelFieldActionUP=std::unique_ptr<IModelFieldAction>;
class IModelFieldAction : public virtual vsc::IModelField {
public:

	virtual ~IModelFieldAction() { }

	virtual const std::vector<IModelActivityScope *> &activities() const = 0;

	virtual void addActivity(IModelActivityScope *a) = 0;

};

}
