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

	virtual bool isCompound() const = 0;

	virtual IModelActivityScope *getActivity() const = 0;

	virtual void setActivity(IModelActivityScope *a) = 0;

};

}
