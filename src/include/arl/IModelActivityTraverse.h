/*
 * IModelActivityTraverse.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelActivity.h"
#include "arl/IModelFieldAction.h"
#include "vsc/IModelConstraint.h"
#include "vsc/IModelField.h"

namespace arl {

class IModelActivityTraverse : public virtual IModelActivity {
public:

	virtual ~IModelActivityTraverse() { }

	virtual IModelFieldAction *getTarget() const = 0;

	virtual vsc::IModelConstraint *getWithC() const = 0;

};
}

