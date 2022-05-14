/*
 * ITypeFieldClaim.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeField.h"

namespace arl {

class ITypeFieldClaim : public virtual vsc::ITypeField {
public:

	virtual ~ITypeFieldClaim() { }

	virtual bool isLock() const = 0;

};

}
