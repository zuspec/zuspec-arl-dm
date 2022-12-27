/*
 * ITypeFieldInOut.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeFieldRef.h"

namespace zsp {
namespace arl {
namespace dm {


class ITypeFieldInOut : public virtual vsc::ITypeFieldRef {
public:

	virtual ~ITypeFieldInOut() { }

	virtual bool isInput() const = 0;

};

}
}
}
