/*
 * ArlImpl.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "arl/IArl.h"
#include "vsc/IDebugMgr.h"

namespace zsp {
namespace arl {
namespace dm {


class ArlImpl;
using ArlImplUP=std::unique_ptr<ArlImpl>;
class ArlImpl : public IArl {
public:
	ArlImpl();

	virtual ~ArlImpl();

	virtual IContext *mkContext(vsc::IContext *ctxt) override;

	virtual void init(vsc::IDebugMgr *dbg_mgr) override;

	vsc::IDebugMgr *getDebugMgr() const { return m_dbg_mgr; }

	static ArlImpl *inst();

private:
	vsc::IDebugMgr				*m_dbg_mgr;
	static ArlImplUP			m_inst;


};

}
}
}

