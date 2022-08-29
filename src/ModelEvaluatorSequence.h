/**
 * ModelEvaluatorSequence.h
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
#include "arl/IModelEvalIterator.h"
#include "arl/impl/VisitorBase.h"
#include "ModelEvaluatorThread.h"

namespace arl {

class ModelEvaluatorSequence : 
    public virtual IModelEvalIterator,
    public virtual VisitorBase {
public:
    ModelEvaluatorSequence(ModelEvaluatorThread *thread);

    ModelEvaluatorSequence(
        ModelEvaluatorThread                *thread,
        const std::vector<IModelActivity *> &activities,
        bool                                owned=false);

    virtual ~ModelEvaluatorSequence();

    void addActivity(IModelActivity *activity, bool owned);

	virtual bool next() override;

	virtual ModelEvalNodeT type() const override;

	virtual IModelFieldAction *action() override;

	virtual IModelEvalIterator *iterator() override;

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override;

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override;

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

private:
    ModelEvaluatorThread                *m_thread;
    int32_t                             m_idx;
    std::vector<IModelActivity *>       m_activities;
    std::vector<IModelActivityUP>       m_activities_up;
    IModelFieldAction                   *m_action;
    IModelEvalIterator                  *m_next_it;
};

}

