/**
 * PoolBindDirective.h
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
#include "zsp/arl/dm/IPoolBindDirective.h"

namespace zsp {
namespace arl {
namespace dm {



class PoolBindDirective : public virtual IPoolBindDirective {
public:
    PoolBindDirective(
        PoolBindKind                kind,
        vsc::dm::ITypeExprFieldRef      *pool,
        vsc::dm::ITypeExprFieldRef      *target);

    virtual ~PoolBindDirective();

    virtual PoolBindKind kind() const override { return m_kind; }

    virtual vsc::dm::ITypeExprFieldRef *getPool() const override {
        return m_pool.get();
    }

    virtual vsc::dm::ITypeExprFieldRef *getTarget() const override {
        return m_target.get();
    }

private:
    PoolBindKind                            m_kind;
    vsc::dm::ITypeExprFieldRefUP                m_pool;
    vsc::dm::ITypeExprFieldRefUP                m_target;

};

}
}
}

