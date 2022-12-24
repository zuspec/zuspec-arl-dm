/*
 * ITypeFieldClaim.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeFieldRef.h"

namespace arl {

class ITypeFieldClaim : public virtual vsc::ITypeFieldRef {
public:

	virtual ~ITypeFieldClaim() { }

	virtual bool isLock() const = 0;

};

}
