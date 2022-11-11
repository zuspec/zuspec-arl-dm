/**
 * TaskElaborateActivityExpandReplicate.h
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
#include <vector>
#include "arl/IContext.h"
#include "arl/impl/VisitorBase.h"

namespace arl {



class TaskElaborateActivityExpandReplicate : public VisitorBase {
public:
    TaskElaborateActivityExpandReplicate(IContext *ctxt);

    virtual ~TaskElaborateActivityExpandReplicate();

    IModelActivityScope *elab(IModelActivityScope *root);

	virtual void visitModelActivityReplicate(IModelActivityReplicate *a) override;

	virtual void visitModelActivityScope(IModelActivityScope *a) override;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

private:
    static vsc::IDebug                  *m_dbg;
    IContext                            *m_ctxt;
    IModelActivityScopeUP               m_result;
    std::vector<IModelActivityScope *>  m_scope_s;

};

}


