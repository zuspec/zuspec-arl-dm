/*
 * TaskBuildActivitySolveModel.cpp
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


TaskBuildActivitySolveModel::TaskBuildActivitySolveModel(IContext *ctxt) : m_ctxt(ctxt) {
    m_root_comp = 0;
}

TaskBuildActivitySolveModel::~TaskBuildActivitySolveModel() {

}

ActivitySolveModel *TaskBuildActivitySolveModel::build(
    IModelFieldComponent           *root_comp,
    IModelActivity                 *root_activity) {
    m_model = ActivitySolveModelUP(new ActivitySolveModel());
    m_root_comp = root_comp;

    m_component_s.push_back(root_comp);
    root_activity->accept(m_this);
    m_component_s.pop_back();

    return m_model.release();
}


void TaskBuildActivitySolveModel::visitModelActivityParallel(
    IModelActivityParallel *a) {
    
    // Traverse branches while managing flow objects
    // 1.) Must collect resources from each branch to ensure uniqueness
    // 2.) Must collect 
    // 


    for (std::vector<IModelActivity *>::const_iterator
        it=a->branches().begin();
        it!=a->branches().end(); it++) {
        (*it)->accept(m_this);
        // At the end of the branch, we should know:
        // - What resources are locked/shared
        // - What buffers are produced by traversals
        // - 
    }

    // TODO: collect streams from first traversal on each branch

}

void TaskBuildActivitySolveModel::visitModelActivitySchedule(
    IModelActivitySchedule *a) {
    // Focus on schedule and nested non-parallel elements
    // Consider parallel to be a carve-out that doesn't 
    // dissolve when included in a schedule 
    //
    // NOTE: Ideally we could treat this as an open region,
    // and resource valid schedule later
    //
    // Perhaps here is where we build a solve structure?
    //
    // We still have lock/share here. Always contribute up to the
    // container's lock/share restrictions

}

void TaskBuildActivitySolveModel::visitModelActivitySequence(
    IModelActivitySequence *a) {
    // If we are inside a schedule block, must record the
    // relationships
    VisitorBase::visitModelActivitySequence(a);
}

void TaskBuildActivitySolveModel::visitModelActivityTraverse(
    IModelActivityTraverse *a) {
    // Update the component map with information for this traversal
    ActivityTraverseData *t_data = TaskBuildActivityTraverseData(
        m_ctxt, m_model.get()).build(m_root_comp, a);
    IDataTypeAction *action_t = a->getTarget()->getDataTypeT<IDataTypeAction>();




    // TODO: create traversal data

}

uint32_t ActivitySolveModel::getComponentId(IModelFieldComponent *c) {
    ActivitySolveModel::AllCompMapT::const_iterator it = all_comp_m.find(c);

    if (it != all_comp_m.end()) {
        return it->second;
    } else {
        uint32_t ret = all_comp_l.size();
        all_comp_l.push_back(c);
        all_comp_m.insert({c, ret});
        return ret;
    }
} 

}
