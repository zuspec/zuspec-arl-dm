/**
 * TaskActionHasMemClaim.h
 *
 * Copyright 2023 Matthew Ballance and Contributors
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
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {



class TaskActionHasMemClaim : 
    public virtual VisitorBase {
public:

    TaskActionHasMemClaim() { };

    virtual ~TaskActionHasMemClaim() { }

    bool check(IDataTypeAction *a) {
        m_has = false;
        m_depth = 0;
        a->accept(m_this);
        return m_has;
    }

    virtual void visitDataTypeAction(IDataTypeAction *t) {
        if (m_depth == 0) {
            m_depth++;
            for (std::vector<vsc::dm::ITypeFieldUP>::const_iterator
                it=t->getFields().begin();
                it!=t->getFields().end(); it++) {
                (*it)->accept(m_this);
            }
            m_depth--;
        }
    }

    virtual void visitTypeFieldAddrClaim(ITypeFieldAddrClaim *t) {
        m_has = true;
    }

    virtual void visitTypeFieldAddrClaimTransparent(ITypeFieldAddrClaimTransparent *t) {
        m_has = true;
    }


private:
    int32_t         m_depth;
    bool            m_has;

};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


