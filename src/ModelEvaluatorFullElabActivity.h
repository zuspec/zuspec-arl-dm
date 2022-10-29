/**
 * ModelEvaluatorFullElabActivity.h
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
#include "arl/IModelEvalIterator.h"
#include "arl/impl/VisitorBase.h"
#include "vsc/IRandState.h"

namespace arl {



class ModelEvaluatorFullElabActivity : 
    public virtual IModelEvalIterator,
    public virtual VisitorBase {
public:
    ModelEvaluatorFullElabActivity(
        IContext                    *ctxt,
        vsc::IRandState             *randstate,
        IModelActivity              *activity);

    virtual ~ModelEvaluatorFullElabActivity();

	virtual bool next() override;

	virtual bool valid() override { return !m_taken; }

	virtual bool pop() override { return false; }

	virtual ModelEvalNodeT type() const override {
        return m_type;
    }

	virtual IModelFieldAction *action() override {
        return m_action;
    }

	virtual IModelEvalIterator *iterator() override {
        return m_iterator;
    }

    virtual void visitModelActivityParallel(IModelActivityParallel *a) override;

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

private:
    static vsc::IDebug              *m_dbg;
    IContext                        *m_ctxt;
    vsc::IRandStateUP               m_randstate;
    IModelActivity                  *m_activity;
    bool                            m_taken;

    ModelEvalNodeT                  m_type;
    IModelFieldAction               *m_action;
    IModelEvalIterator              *m_iterator;

};

}


