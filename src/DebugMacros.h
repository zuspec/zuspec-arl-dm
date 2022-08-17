
#ifndef INCLUDED_DEBUG_MACROS_H
#define INCLUDED_DEBUG_MACROS_H
#else
#error DebugMacros.h can only be included in a .cpp file
#endif
#include "vsc/IDebug.h"
#include "ArlImpl.h"

#ifndef LIBARL_DISABLE_DEBUG
static vsc::IDebug *__dbg = 0;

#define DEBUG_INIT(scope) \
    if (!__dbg) { \
        __dbg = (ArlImpl::inst()->getDebugMgr())?(ArlImpl::inst()->getDebugMgr())->findDebug(scope):0; \
    }
#define DEBUG_ENTER(fmt, ...) \
    if (__dbg && __dbg->en()) __dbg->enter(fmt, ##__VA_ARGS__)
#define DEBUG_LEAVE(fmt, ...) \
    if (__dbg && __dbg->en()) __dbg->leave(fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) \
    if (__dbg && __dbg->en()) __dbg->debug(fmt, ##__VA_ARGS__)

#else /* LIBARL_DISABLE_DEBUG */
#define DEBUG_INIT(scope)
#define DEBUG_ENTER(fmt, ...)
#define DEBUG_LEAVE(fmt, ...)
#define DEBUG(fmt, ...)

#endif
