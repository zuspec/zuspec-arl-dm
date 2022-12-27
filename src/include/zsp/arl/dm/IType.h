/*
 * IType.h
 *
 *  Created on: Apr 2, 2022
 *      Author: mballance
 */

#pragma once
#include <string>
#include "arl/IAccept.h"

namespace zsp {
namespace arl {
namespace dm {


class IType : public IAccept {
public:

	virtual ~IType() { }

	virtual const std::string &fullName() const = 0;

	virtual const std::string &name() const = 0;

};

}
}
}
