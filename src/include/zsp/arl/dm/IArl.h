/*
 * IArl.h
 *
 *  Created on: Apr 3, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IContext.h"
#include "dmgr/IDebugMgr.h"

namespace zsp {
namespace arl {
namespace dm {


class IArl {
public:

	virtual ~IArl() { }

	virtual void init(dmgr::IDebugMgr *dbg_mgr) = 0;

	virtual IContext *mkContext(vsc::dm::IContext *ctxt) = 0;

};

}
}
}
