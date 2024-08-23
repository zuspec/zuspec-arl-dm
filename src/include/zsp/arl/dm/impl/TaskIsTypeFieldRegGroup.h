/**
 * TaskIsTypeFieldRegGroup.h
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



class TaskIsTypeFieldRegGroup :
    public virtual arl::dm::VisitorBase {
public:

    virtual ~TaskIsTypeFieldRegGroup() { }

    bool check(vsc::dm::ITypeField *f) {
        m_ret = false;
        f->accept(m_this);
        return m_ret;
    }

    virtual void visitTypeFieldRegGroup(arl::dm::ITypeFieldRegGroup *f) override {
        m_ret = true;
    }

    virtual void visitTypeFieldRegGroupArr(arl::dm::ITypeFieldRegGroupArr *f) override {
        m_ret = true;
    }

private:
    bool            m_ret;


};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


