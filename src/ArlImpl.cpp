/*
 * ArlImpl.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "ArlImpl.h"
#include "Context.h"

namespace arl {

ArlImpl::ArlImpl() {
	// TODO Auto-generated constructor stub

}

ArlImpl::~ArlImpl() {
	// TODO Auto-generated destructor stub
}

IContext *ArlImpl::mkContext(vsc::IContext *ctxt) {
	return new Context(ctxt);
}

ArlImpl *ArlImpl::inst() {
	if (!m_inst) {
		m_inst = ArlImplUP(new ArlImpl());
	}
	return m_inst.get();
}

extern "C" IArl *iarl() {
	return ArlImpl::inst();
}

ArlImplUP ArlImpl::m_inst;

} /* namespace arl */
