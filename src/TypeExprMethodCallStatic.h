/**
 * TypeExprMethodCallStatic.h
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
#include "zsp/arl/dm/ITypeExprMethodCallStatic.h"

namespace zsp {
namespace arl {
namespace dm {



class TypeExprMethodCallStatic : public virtual ITypeExprMethodCallStatic {
public:
    TypeExprMethodCallStatic(
        IDataTypeFunction                           *target,
        const std::vector<vsc::dm::ITypeExpr *>     &params,
        bool                                        owned);

    virtual ~TypeExprMethodCallStatic();

    virtual IDataTypeFunction *getTarget() const override {
        return m_target;
    }

    virtual const std::vector<vsc::dm::ITypeExprUP> &getParameters() const override {
        return m_params;
    }

    virtual std::vector<vsc::dm::ITypeExprUP> &getParameters() override {
        return m_params;
    }
    
    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    IDataTypeFunction                               *m_target;
    std::vector<vsc::dm::ITypeExprUP>                m_params;
};

}
}
}


