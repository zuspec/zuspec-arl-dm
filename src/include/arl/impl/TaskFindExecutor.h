/**
 * TaskFindExecutor.h
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
#include "arl/IModelFieldExecutor.h"
#include "arl/impl/VisitorBase.h"

namespace arl {



class TaskFindExecutor : public VisitorBase {
public:

    TaskFindExecutor() : m_executor(0) { }

    virtual ~TaskFindExecutor() { }

    IModelFieldExecutor *find(vsc::IModelField *f) {
        m_executor = 0;
        f->accept(m_this);
        return m_executor;
    }

    virtual void visitModelField(vsc::IModelField *f) override {
        // Block from recursing
    }

	virtual void visitModelFieldExecutorClaim(IModelFieldExecutorClaim *f) override {
        m_executor = dynamic_cast<IModelFieldExecutor *>(f->getRef());
    }

private:
    IModelFieldExecutor                 *m_executor;

};

} /* namespace arl */


