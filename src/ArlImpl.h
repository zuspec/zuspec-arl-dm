/*
 * ArlImpl.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "arl/IArl.h"

namespace arl {

class ArlImpl;
using ArlImplUP=std::unique_ptr<ArlImpl>;
class ArlImpl : public IArl {
public:
	ArlImpl();

	virtual ~ArlImpl();

	virtual IContext *mkContext(vsc::IContext *ctxt) override;

	static ArlImpl *inst();

private:
	static ArlImplUP			m_inst;


};

} /* namespace arl */

