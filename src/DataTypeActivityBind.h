/**
 * DataTypeActivityBind.h
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
#include "arl/IDataTypeActivityBind.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypeActivityBind : public virtual IDataTypeActivityBind {
public:
    DataTypeActivityBind(const std::vector<vsc::ITypeExprFieldRef *> &targets);

    virtual ~DataTypeActivityBind();

    virtual const std::vector<vsc::ITypeExprFieldRefUP> &getTargets() const override {
        return m_targets;
    }

    virtual void accept(vsc::IVisitor *v) override;

private:
    std::vector<vsc::ITypeExprFieldRefUP>           m_targets;

};

}
}
}


