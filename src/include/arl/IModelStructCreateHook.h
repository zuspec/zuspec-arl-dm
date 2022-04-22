/*
 * IModelStructCreateHook.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelField.h"

namespace arl {

class IModelStructCreateHook {
public:

	virtual ~IModelStructCreateHook() { }

	virtual void create(vsc::IModelField *field) = 0;
};

}
