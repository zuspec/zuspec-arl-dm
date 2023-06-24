/**
 * TypeExecGroup.h
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
#include "zsp/arl/dm/ITypeExecGroup.h"

namespace zsp {
namespace arl {
namespace dm {



class TypeExecGroup : public virtual ITypeExecGroup {
public:
    TypeExecGroup(
        ExecKindT           kind,
        ITypeExecGroup      *super);

    virtual ~TypeExecGroup();

    virtual ExecKindT getKind() const override {
        return m_kind;
    }

    virtual const std::vector<ITypeExecUP> &getExecs() const override {
        return m_execs;
    }

    virtual void addExec(ITypeExec *e) override {
        m_execs.push_back(ITypeExecUP(e));
    }

    virtual ITypeExecGroup *getSuper() const override {
        return m_super;
    }

private:
    ExecKindT                   m_kind;
    ITypeExecGroup              *m_super;
    std::vector<ITypeExecUP>    m_execs;

};

}
}
}


