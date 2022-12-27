/*
 * ITypeFieldPool.h
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/ITypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class ITypeFieldPool : public virtual vsc::ITypeField {
public:

	virtual ~ITypeFieldPool() { }

	virtual int32_t getDeclSize() = 0;

};

}
}
}
