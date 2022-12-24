/**
 * TaskVisitActionTypeClaimRef.h
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
#include "arl/impl/VisitorBase.h"

namespace arl {


class TaskVisitActionTypeClaimRef : public VisitorBase {
public:
    TaskVisitActionTypeClaimRef(
        const std::function<void (ITypeFieldInOut *)>  &ref_f,
        const std::function<void (ITypeFieldClaim *)>  &claim_f
    ) : m_depth(0), m_ref_f(ref_f), m_claim_f(claim_f) { }

    virtual ~TaskVisitActionTypeClaimRef() { }

    void visit(IDataTypeAction *t) {
        t->accept(m_this);
    }

	virtual void visitDataTypeAction(IDataTypeAction *i) override {
        if (!m_depth) {
            m_depth++;
            VisitorBase::visitDataTypeAction(i);
            m_depth--;
        }
    }

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) override {
        m_ref_f(f);
    }

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) override {
        m_claim_f(f);
    }

private:
    int32_t                                   m_depth;
    std::function<void (ITypeFieldInOut *)>   m_ref_f;
    std::function<void (ITypeFieldClaim *)>   m_claim_f;
};

}


