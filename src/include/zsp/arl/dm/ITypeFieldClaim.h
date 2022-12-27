/*
 * ITypeFieldClaim.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeFieldRef.h"

namespace zsp {
namespace arl {
namespace dm {


class ITypeFieldClaim : public virtual vsc::dm::ITypeFieldRef {
public:

	virtual ~ITypeFieldClaim() { }

	virtual bool isLock() const = 0;

};

}
}
}
