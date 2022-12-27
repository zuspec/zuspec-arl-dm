/*
 * IArl.h
 *
 *  Created on: Apr 3, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IContext.h"
#include "vsc/IDebugMgr.h"

namespace zsp {
namespace arl {
namespace dm {


class IArl {
public:

	virtual ~IArl() { }

	virtual void init(vsc::IDebugMgr *dbg_mgr) = 0;

	virtual IContext *mkContext(vsc::IContext *ctxt) = 0;

};

}
}
}
