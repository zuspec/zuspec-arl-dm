/*
 * IModelFieldComponent.h
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IComponentMap.h"
#include "vsc/dm/IModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelFieldComponent;
using IModelFieldComponentUP=vsc::dm::UP<IModelFieldComponent>;
class IModelFieldComponent : 
	public virtual vsc::dm::IModelField {
public:
	virtual ~IModelFieldComponent() { }

	virtual int32_t getId() const = 0;

	virtual void setId(int32_t i) = 0;

};

}
}
}
