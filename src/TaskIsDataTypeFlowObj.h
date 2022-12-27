/**
 * TaskIsDataTypeFlowObj.h
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
#include "arl/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {


class TaskIsDataTypeFlowObj : public VisitorBase {
public:
    TaskIsDataTypeFlowObj();

    TaskIsDataTypeFlowObj(FlowObjKindE kind);

    virtual ~TaskIsDataTypeFlowObj();

    static bool test(vsc::IDataType *t);

    static bool test(FlowObjKindE kind, vsc::IDataType *t);

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override;

private:
    bool                m_ret;
    bool                m_check_kind;
    FlowObjKindE        m_kind;

};

}
}
}

