/*
 * ITypeFieldInOut.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeFieldRef.h"

namespace zsp {
namespace arl {
namespace dm {


class ITypeFieldInOut : public virtual vsc::dm::ITypeFieldRef {
public:

	virtual ~ITypeFieldInOut() { }

	virtual bool isInput() const = 0;

};

}
}
}
