/**
 * TaskElaborateActivity.h
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
#include "arl/impl/VisitorBase.h"

namespace arl {

struct ElabActivity {
    std::vector<IModelActivityScopeUP>      activity_s;
    IModelActivityScope                     *root;
};
using ElabActivityUP=std::unique_ptr<ElabActivity>;

class TaskElaborateActivity : public VisitorBase {
public:
    TaskElaborateActivity(IContext *ctxt);

    virtual ~TaskElaborateActivity();

    /**
     * @brief Builds an activity from a component tree and action type
     * 
     * @param root_comp 
     * @param root_action 
     * @return IModelActivity* 
     */
    ElabActivity *elaborate(
        vsc::IRandState             *randstate,
        IModelFieldComponent        *root_comp,
        IDataTypeAction             *root_action);

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

private:
    enum class StepT {

    };

private:

    void process_scope(IModelActivityScope *s);

    void process_traversal(IModelActivityTraverse *t);

private:
    IContext                        *m_ctxt;
    ElabActivityUP                  m_activity;
    int32_t                         m_scope_search_depth;
    int32_t                         m_action_depth;
    int32_t                         m_action_target_depth;
    bool                            m_more_work;
    bool                            m_changed;

};

}


