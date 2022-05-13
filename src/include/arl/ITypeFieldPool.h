/*
 * ITypeFieldPool.h
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeField.h"

namespace arl {

class ITypeFieldPool : public vsc::ITypeField {
public:

	virtual ~ITypeFieldPool() { }

	virtual int32_t getDeclSize() = 0;

};

}
