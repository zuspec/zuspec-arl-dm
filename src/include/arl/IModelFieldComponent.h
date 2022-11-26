/*
 * IModelFieldComponent.h
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IComponentMap.h"
#include "vsc/IModelField.h"

namespace arl {

class IModelFieldComponent;
using IModelFieldComponentUP=std::unique_ptr<IModelFieldComponent>;
class IModelFieldComponent : 
	public virtual vsc::IModelField {
public:
	virtual ~IModelFieldComponent() { }

	virtual int32_t getId() const = 0;

};

}
