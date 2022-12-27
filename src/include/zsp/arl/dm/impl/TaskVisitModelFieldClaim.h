/**
 * TaskVisitModelFieldClaim.h
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
#include <functional>
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {


class TaskVisitModelFieldClaim : public VisitorBase {
public:
    TaskVisitModelFieldClaim(
        const std::function<void (IModelFieldClaim *)> &func) : 
            m_func(func), m_depth(0) { }

    virtual ~TaskVisitModelFieldClaim() { }

    void visit(IModelFieldAction *action) {
        m_depth = 0;
        action->accept(m_this);
    }

	virtual void visitModelFieldAction(IModelFieldAction *f) override {
        if (!m_depth) {
            m_depth++;
            VisitorBase::visitModelFieldAction(f);
            m_depth--;
        }
    }

	virtual void visitModelFieldClaim(IModelFieldClaim *f) override {
        m_func(f);
    }

private:
    uint32_t                                        m_depth;
    std::function<void (IModelFieldClaim *)>        m_func;
};

}
}
}


