/*
 * TaskBuildActivityTraverseData.cpp
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
#include "TaskBuildActivitySolveModel.h"
#include "TaskBuildActivityTraverseData.h"


namespace arl {


TaskBuildActivityTraverseData::TaskBuildActivityTraverseData(
    IContext                *ctxt,
    ActivitySolveModel      *solve_model) : m_ctxt(ctxt), m_solve_model(solve_model) {
    m_root_comp = 0;
}

TaskBuildActivityTraverseData::~TaskBuildActivityTraverseData() {

}

ActivityTraverseData *TaskBuildActivityTraverseData::build(
    IModelFieldComponent        *root_comp,
    IModelActivityTraverse      *t) {
    // Get all the component instances where this action could execute
    m_root_comp = root_comp;

    IDataTypeAction *action_t = t->getTarget()->getDataTypeT<IDataTypeAction>();
#ifdef UNDEFINED
    std::vector<IModelFieldComponent *> contexts = m_root_comp->getCompMap()->getSubContexts(
        action_t->getComponentType());
    
    m_data = ActivityTraverseDataUP(new ActivityTraverseData(t));

    // Ensure all available contexts are added 
    for (std::vector<IModelFieldComponent *>::const_iterator
        it=contexts.begin();
        it!=contexts.end(); it++) {
        // Ensure all components up the hierarchy are added
        IModelFieldComponent *c = *it;
        m_data->comp_ctxt_l.push_back(m_solve_model->getComponentId(c));

        // Ensure all components up the tree exist
        while (c->getParent()) {
            c = c->getParentT<IModelFieldComponent>();
            m_solve_model->getComponentId(c);
        }
    }
#endif

//    ActivitySolveModel::AllCompMapT::const_iterator it = m_model->all_comp_m.find()
}

}
