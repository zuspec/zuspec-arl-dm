/*
 * IAccept.h
 *
 *  Created on: Apr 2, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IVisitor.h"

namespace zsp {
namespace arl {
namespace dm {


class IAccept {
public:

	virtual ~IAccept () { }

	virtual void accept(IVisitor *v) = 0;

};

}
}
}

