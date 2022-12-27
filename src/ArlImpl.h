/*
 * ArlImpl.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "zsp/arl/dm/IArl.h"
#include "dmgr/IDebugMgr.h"

namespace zsp {
namespace arl {
namespace dm {


class ArlImpl;
using ArlImplUP=std::unique_ptr<ArlImpl>;
class ArlImpl : public IArl {
public:
	ArlImpl();

	virtual ~ArlImpl();

	virtual IContext *mkContext(vsc::dm::IContext *ctxt) override;

	virtual void init(dmgr::IDebugMgr *dbg_mgr) override;

	dmgr::IDebugMgr *getDebugMgr() const { return m_dbg_mgr; }

	static ArlImpl *inst();

private:
	dmgr::IDebugMgr				*m_dbg_mgr;
	static ArlImplUP			m_inst;


};

}
}
}

