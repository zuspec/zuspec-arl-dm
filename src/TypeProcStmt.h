/**
 * TypeProcStmt.h
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
#include "zsp/arl/dm/ITypeProcStmt.h"

namespace zsp {
namespace arl {
namespace dm {


class TypeProcStmt :
    public virtual ITypeProcStmt {
public:
    TypeProcStmt();

    virtual ~TypeProcStmt();

    virtual vsc::dm::IAssociatedData *getAssociatedData() const override {
        return m_assoc_data.get();
    }

    virtual void setAssociatedData(vsc::dm::IAssociatedData *d, bool owned=true) override {
        m_assoc_data = vsc::dm::IAssociatedDataUP(d, owned);
    }

protected:
    vsc::dm::IAssociatedDataUP          m_assoc_data;


};

}
}
}


