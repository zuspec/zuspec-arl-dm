/**
 * IFactory.h
 *
 * Copyright 2022 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author: 
 */
#pragma once
#include <iostream>
#include "dmgr/IDebugMgr.h"
#include "vsc/dm/IContext.h"
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IContextDumper.h"
#include "zsp/arl/dm/IContextLoader.h"
#include "zsp/arl/dm/IRewriteContext.h"
#include "zsp/arl/dm/ITypeModelDumper.h"

namespace zsp {
namespace arl {
namespace dm {



class IFactory {
public:

    virtual ~IFactory() { }

    virtual void init(dmgr::IDebugMgr *dmgr) = 0;

    virtual dmgr::IDebugMgr *getDebugMgr() = 0;

    virtual IContext *mkContext(vsc::dm::IContext *ctxt) = 0;

    virtual IRewriteContext *mkRewriteContext(
            IContext                                *ctxt,
            const std::vector<vsc::dm::IAccept *>   &roots) = 0;

    virtual ITypeModelDumper *mkTypeModelDumperJSON(
        std::ostream *out, int32_t indent) = 0;

//    virtual IContextDumper *mkContextDumperJSON(std::ostream *out) = 0;


};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


