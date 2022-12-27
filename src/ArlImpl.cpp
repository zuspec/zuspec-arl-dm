/*
 * ArlImpl.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "ArlImpl.h"
#include "Context.h"

namespace zsp {
namespace arl {
namespace dm {


ArlImpl::ArlImpl() {
	m_dbg_mgr = 0;
}

ArlImpl::~ArlImpl() {
	// TODO Auto-generated destructor stub
}

IContext *ArlImpl::mkContext(vsc::dm::IContext *ctxt) {
	return new Context(ctxt);
}

void ArlImpl::init(dmgr::IDebugMgr *dbg_mgr) {
	m_dbg_mgr = dbg_mgr;
};

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

}
} /* namespace arl */
}
