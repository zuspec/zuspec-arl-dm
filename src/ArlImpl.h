/*
 * ArlImpl.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IArl.h"

namespace arl {

class ArlImpl : public IArl {
public:
	ArlImpl();

	virtual ~ArlImpl();

	virtual IContext *mkContext(vsc::IContext *ctxt) override;

};

} /* namespace arl */

