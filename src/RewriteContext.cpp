/*
 * RewriteContext.cpp
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
#include "RewriteContext.h"


namespace zsp {
namespace arl {
namespace dm {

#ifdef UNDEFINED
RewriteContext::RewriteContext(
    IContext                                *ctxt,
    const std::vector<vsc::dm::IAccept *>   &roots) : ContextDelegator(ctxt, false) {
    
    m_context_s.push_back({});
    for (std::vector<vsc::dm::IAccept *>::const_iterator
        it=roots.begin();
        it!=roots.end(); it++) {
        m_context_s.back().push_back(vsc::dm::UP<vsc::dm::IAccept>(*it, false));
    }
}

RewriteContext::~RewriteContext() {

}

const std::vector<vsc::dm::IAcceptUP> &RewriteContext::getRoots() const {
    return m_context_s.back();
}

void RewriteContext::setRoot(int32_t idx, vsc::dm::IAccept *r, bool owned) {
    m_context_s.back().at(idx) = vsc::dm::IAcceptUP(r, owned);
}

void RewriteContext::addRoot(vsc::dm::IAccept *r, bool owned) {
    m_context_s.back().push_back(vsc::dm::IAcceptUP(r, owned));
}

void RewriteContext::pushContext() {
    m_context_s.push_back({});
    const std::vector<vsc::dm::IAcceptUP> &prev = m_context_s.at(m_context_s.size()-2);
    std::vector<vsc::dm::IAcceptUP> &back = m_context_s.back();

    for (std::vector<vsc::dm::IAcceptUP>::const_iterator
        it=prev.begin();
        it!=prev.end(); it++) {
        back.push_back(vsc::dm::IAcceptUP(it->get(), false));
    }
}

void RewriteContext::popContext() {
    if (m_context_s.size() > 1) {
        m_context_s.pop_back();
    }
}

int32_t RewriteContext::contextDepth() {
    return m_context_s.size()-1;
}

#endif /* UNDEFINED */

}
}
}
