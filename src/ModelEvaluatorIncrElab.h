/**
 * ModelEvaluatorIncrElab.h
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
#include "arl/IModelEvaluator.h"
#include "arl/impl/VisitorBase.h"

namespace arl {



class ModelEvaluatorIncrElab : public virtual IModelEvaluator, public VisitorBase {
public:
    ModelEvaluatorIncrElab(IContext *ctxt);

    virtual ~ModelEvaluatorIncrElab();

    virtual IModelEvalIterator *eval(
        const vsc::IRandState           *randstate,
        IModelFieldComponent            *root_comp,
        IDataTypeAction                 *root_action) override;

	virtual IModelEvalIterator *next();

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

private:
    static vsc::IDebug              *m_dbg;
    IContext                        *m_ctxt;
	vsc::IRandStateUP				m_randstate;
	IModelFieldActionUP				m_action;
	IModelActivityTraverseUP		m_dummy_activity;
	uint32_t						m_activity_idx;
	std::vector<IModelActivity *>	m_activities;
	IModelEvalIterator				*m_next;

};

}


