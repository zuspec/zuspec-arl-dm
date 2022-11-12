/**
 * TaskElaborateActivitySelectReplicateSizes.h
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
#include <unordered_set>
#include "arl/IContext.h"
#include "arl/impl/VisitorBase.h"
#include "vsc/impl/DebugMacros.h"

namespace arl {



class TaskElaborateActivitySelectReplicateSizes : public VisitorBase {
public:
    TaskElaborateActivitySelectReplicateSizes(IContext *ctxt);

    virtual ~TaskElaborateActivitySelectReplicateSizes();

    bool eval(
        vsc::IRandState     *randstate,
        IModelActivity      *root);

	virtual void visitModelActivityReplicate(IModelActivityReplicate *a) override;

	virtual void visitModelActivityScope(IModelActivityScope *a) override;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

private:
    static vsc::IDebug                          *m_dbg;
    IContext                                    *m_ctxt;
    std::vector<vsc::IModelField *>             m_count_fields;
    std::unordered_set<vsc::IModelConstraint *> m_constraint_s;
    std::vector<vsc::IModelConstraint *>        m_constraints;
};

}


