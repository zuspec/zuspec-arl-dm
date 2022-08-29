/*
 * IModelFieldComponent.h
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelField.h"

namespace arl {

class IModelFieldComponent : public virtual vsc::IModelField {
public:
	virtual ~IModelFieldComponent() { }

	/**
	 * Builds the component map across the tree
	 */
	virtual void initCompTree() = 0;

};

}
