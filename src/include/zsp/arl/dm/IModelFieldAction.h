/*
 * IModelFieldAction.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IModelActivityScope.h"
#include "vsc/dm/IModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelFieldAction;
using IModelFieldActionUP=std::unique_ptr<IModelFieldAction>;
class IModelFieldAction : public virtual vsc::dm::IModelField {
public:

	virtual ~IModelFieldAction() { }

	virtual bool isCompound() const = 0;

	virtual IModelActivityScope *getActivity() const = 0;

	virtual void setActivity(IModelActivityScope *a) = 0;

};

}
}
}
