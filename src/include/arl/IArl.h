/*
 * IArl.h
 *
 *  Created on: Apr 3, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"

namespace arl {

class IArl {
public:

	virtual ~IArl() { }

	virtual IContext *mkContext(vsc::IContext *ctxt) = 0;

};

}
