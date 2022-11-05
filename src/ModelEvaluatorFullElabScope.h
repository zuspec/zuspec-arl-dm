/**
 * ModelEvaluatorFullElabScope.h
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
#include "arl/IContext.h"
#include "arl/IModelActivityScope.h"
#include "arl/IModelEvalIterator.h"
#include "arl/impl/VisitorBase.h"
#include "vsc/IRandState.h"

namespace arl {


class ModelEvaluatorFullElabScope :
    public virtual IModelEvalIterator,
    public virtual VisitorBase {
public:
    ModelEvaluatorFullElabScope(
        IContext                *ctxt,
        vsc::IRandState         *randstat,
        IModelActivityScope     *scope
    );

    virtual ~ModelEvaluatorFullElabScope();

	virtual bool next() override;

	virtual bool valid() override;

	virtual bool pop() override;

	virtual ModelEvalNodeT type() const override;

	virtual IModelFieldAction *action() override;

	virtual IModelEvalIterator *iterator() override;

	virtual void visitModelActivityScope(IModelActivityScope *a) override;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

private:
    static vsc::IDebug              *m_dbg;
    IContext                        *m_ctxt;
    vsc::IRandStateUP               m_randstate;
    IModelActivityScope             *m_scope;
    int32_t                         m_idx;

    ModelEvalNodeT                  m_type;
    IModelFieldAction               *m_action;
    IModelEvalIterator              *m_iterator;

};

}


