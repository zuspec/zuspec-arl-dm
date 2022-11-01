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
#include "TaskBuildActivitySolveModel.h"
#include "TaskBuildActivityTraverseData.h"
#include "TaskElaborateActivity.h"


namespace arl {


TaskElaborateActivity::TaskElaborateActivity(IContext *ctxt) : m_ctxt(ctxt) {

}

TaskElaborateActivity::~TaskElaborateActivity() {

}

IModelActivity *TaskElaborateActivity::elaborate(
    IModelFieldComponent            *root_comp,
    IDataTypeAction                 *root_action) {
    bool ret = true;

    ModelBuildContext build_ctxt(m_ctxt);
    IModelFieldAction *root_action_f = root_action->mkRootFieldT<IModelFieldAction>(
        &build_ctxt,
        root_action->name(),
        false
    );

    IModelActivitySequence *seq = m_ctxt->mkModelActivitySequence();
    if (root_action_f->activities().size() == 0) {
        // Traveral of a leaf-level action
        // Need to add a synthetic traveral to the root sequence
        seq->addActivity(m_ctxt->mkModelActivityTraverse(root_action_f, 0), true);
    } else if (root_action_f->activities().size() == 1) {

        // Add a traversal for the compound activity
        seq->addActivity(m_ctxt->mkModelActivityTraverse(root_action_f, 0), true);

        // Add the root activities inside the sequence
        seq->addActivity(root_action_f->activities().at(0), false);
    } else {
        // Multiple activities. Add a schedule block inside the top-level sequence
        IModelActivitySchedule *sched = m_ctxt->mkModelActivitySchedule();
        for (std::vector<IModelActivityScope *>::const_iterator
            it=root_action_f->activities().begin();
            it!=root_action_f->activities().end(); it++) {
            sched->addActivity(*it, false);
        }
        seq->addActivity(sched, true);
    }

    // The activity owns the root action
    seq->addField(root_action_f);
    m_activity = IModelActivityUP(seq);
    
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
    ActivitySolveModelUP solve_model(TaskBuildActivitySolveModel(m_ctxt).build(
        root_comp,
        m_activity.get()));

    // 2.) Solve

    // 3.) Collect result of solve

    // 4.) Update model if required and jump to 1

    // end.) If solve is successful, update comp, claim, and flow-object references

    return m_activity.release();
}

}