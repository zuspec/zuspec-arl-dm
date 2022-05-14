/*
 * ITypeFieldInOut.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeField.h"

namespace arl {

class ITypeFieldInOut : public virtual vsc::ITypeField {
public:

	virtual ~ITypeFieldInOut() { }

	virtual bool isInput() const = 0;

};

}
