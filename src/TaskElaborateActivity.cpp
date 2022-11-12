/*
 * TaskElaborateActivity.cpp
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
#include "arl/impl/ModelBuildContext.h"
#include "vsc/impl/TaskSetUsedRand.h"
#include "TaskBuildActivitySolveModel.h"
#include "TaskBuildActivityTraverseData.h"
#include "TaskElaborateActivity.h"
#include "TaskElaborateActivityExpandReplicate.h"


namespace arl {


TaskElaborateActivity::TaskElaborateActivity(IContext *ctxt) : m_ctxt(ctxt) {

}

TaskElaborateActivity::~TaskElaborateActivity() {

}

ElabActivity *TaskElaborateActivity::elaborate(
    vsc::IRandState                 *randstate,
    IModelFieldComponent            *root_comp,
    IDataTypeAction                 *root_action) {
    bool ret = true;

    ModelBuildContext build_ctxt(m_ctxt);
    IModelFieldAction *root_action_f = root_action->mkRootFieldT<IModelFieldAction>(
        &build_ctxt,
        root_action->name(),
        false
    );

    // Mark all declared-random fields as used-random
    vsc::TaskSetUsedRand().apply(root_action_f, true);

    IModelActivityScope *seq = m_ctxt->mkModelActivityScope(ModelActivityScopeT::Sequence);
    seq->addActivity(m_ctxt->mkModelActivityTraverse(
        root_action_f, 
        0,
        false,
        root_action_f->getActivity(),
        false), true);

    // The activity owns the root action
    seq->addField(root_action_f);

    m_activity = ElabActivityUP(new ElabActivity());
    m_activity->activity_s.push_back(IModelActivityScopeUP(seq));

    // Gen2: expand all replicate scopes
    m_activity->activity_s.push_back(IModelActivityScopeUP(
        TaskElaborateActivityExpandReplicate(m_ctxt).elab(
            randstate,
            m_activity->activity_s.back().get()
        )));

    // Gen3: Assign flow-object claims and infer actions as needed

    // Gen4: Process resources and schedule
    
    // 1.) Build solve model for resource and flow-object assignments
    //     a.) Need to know full set of valid component instances, 
    //         resources, and flow objects. Must sub-organize these by
    //         type, since our selection between then will be type-specific
    //
    //     b.) Need to know, per reference, of any structural restrictions.
    //         For example, actions have restrictions based on parent context.
    //         For example, state and buffer references have restrictions based
    //         on preceeding actions.
    //         Need to also collect structural restrictions around concurrent
    //         execution. These are best discovered during traversal
    //
    //     c.) Need to know 
    // ActivitySolveModelUP solve_model(TaskBuildActivitySolveModel(m_ctxt).build(
    //     root_comp,
    //     m_activity->activity_s.back().get()));

    // 2.) Solve

    // 3.) Collect result of solve

    // 4.) Update model if required and jump to 1

    // end.) If solve is successful, update comp, claim, and flow-object references

    m_activity->root = m_activity->activity_s.back().get();

    return m_activity.release();
}

void TaskElaborateActivity::visitModelActivityTraverse(IModelActivityTraverse *a) {
#ifdef UNDEFINED
    if (a->getTarget()->isCompound()) {
        if (m_target_depth == m_depth) {
            // TODO: gather requirements from this level
            // TODO: perform expansion if required
        } else if (m_target_depth > m_depth) {
            m_depth++;
            a->getTarget();
            m_depth--;
        } else {
            // We haven't entered the compound below yet
            m_more_work = true;
        }
    }
#endif
}

void TaskElaborateActivity::process_scope(IModelActivityScope *s) {
    bool more_work = false;

    // TODO: need some indication as to how deep to dig. Could 
    // be multiple levels of scope before we reach the 

    for (std::vector<IModelActivity *>::const_iterator
        it=s->activities().begin();
        it!=s->activities().end(); it++) {
        // Always propagate 'false' down
        m_more_work = false;
        m_scope_search_depth++;
        (*it)->accept(m_this);
        m_scope_search_depth--;
        more_work |= m_more_work;
    }

    if (m_scope_search_depth == 0) {
        // This is the scope 
        m_more_work = false;
        m_action_target_depth++;

        // Go back to handle the next level of compound 
        for (std::vector<IModelActivity *>::const_iterator
            it=s->activities().begin();
            it!=s->activities().end(); it++) {
            (*it)->accept(m_this);
        }
    }    

    // Propagate the result of whether we 
    m_more_work = more_work;
}

void TaskElaborateActivity::process_traversal(IModelActivityTraverse *t) {

}

}
