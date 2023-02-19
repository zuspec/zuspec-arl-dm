/*
 * Factory.cpp
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
#include "zsp/arl/dm/FactoryExt.h"
#include "Context.h"
#include "Factory.h"
#include "RewriteContext.h"
#include "TypeModelDumperJSON.h"

namespace zsp {
namespace arl {
namespace dm {


Factory::Factory() : m_dmgr(0) {

}

Factory::~Factory() {

}

void Factory::init(dmgr::IDebugMgr *dmgr) {
    m_dmgr = dmgr;
}

dmgr::IDebugMgr *Factory::getDebugMgr() {
    return m_dmgr;
}

IContext *Factory::mkContext(vsc::dm::IContext *ctxt) {
    return new Context(ctxt);
}

IRewriteContext *Factory::mkRewriteContext(
            IContext                                *ctxt,
            const std::vector<vsc::dm::IAccept *>   &roots) {
    return new RewriteContext(ctxt, roots);
}

ITypeModelDumper *Factory::mkTypeModelDumperJSON(
    std::ostream *out, int32_t indent) {
    return new TypeModelDumperJSON(m_dmgr, out, indent);
}

IFactory *Factory::inst() {
    if (!m_inst) {
        m_inst = FactoryUP(new Factory());
    }
    return m_inst.get();
}

FactoryUP Factory::m_inst;

}
}
}

zsp::arl::dm::IFactory *zsp_arl_dm_getFactory() {
    return zsp::arl::dm::Factory::inst();
}