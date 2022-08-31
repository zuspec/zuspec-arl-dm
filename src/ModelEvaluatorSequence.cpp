/*
 * ModelEvaluatorSequence.cpp
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
#include "DebugMacros.h"
#include "ModelEvaluatorParallel.h"
#include "ModelEvaluatorSequence.h"
#include "TaskCollectTopLevelActivities.h"


namespace arl {
ModelEvaluatorSequence::ModelEvaluatorSequence(ModelEvaluatorThread *thread) 
    : m_idx(-1), m_thread(thread), m_action(0), m_next_it(0) {
    DEBUG_INIT("ModelEvaluatorSequence");
}

ModelEvaluatorSequence::ModelEvaluatorSequence(
        ModelEvaluatorThread                *thread,
        const std::vector<IModelActivity *> &activities,
        bool                                owned) : m_idx(-1), m_thread(thread),
        m_activities(activities.begin(), activities.end()) {

    if (owned) {
        for (std::vector<IModelActivity *>::const_iterator
            it=activities.begin();
            it!=activities.end(); it++) {
            m_activities_up.push_back(IModelActivityUP(*it));
        }
    }
}

ModelEvaluatorSequence::~ModelEvaluatorSequence() {

}

void ModelEvaluatorSequence::addActivity(IModelActivity *activity, bool owned) {
    m_activities.push_back(activity);
    if (owned) {
        m_activities_up.push_back(IModelActivityUP(activity));
    }
}

bool ModelEvaluatorSequence::next() {
    DEBUG_ENTER("next m_idx=%d sz=%d", (m_idx+1), m_activities.size());
    m_idx++;

    if (m_idx >= m_activities.size()) {
        delete this;
        return false;
    }

    m_action = 0;
    m_next_it = 0;

    // Process the next entry on the activities list. The resulting
    // content of 'action' and 'next_it' determines what happens
    // next
    m_activities.at(m_idx)->accept(m_this);

    if (m_action) {
        DEBUG_LEAVE("next - action to execute");
        return true;
    } else if (m_next_it) {
        IModelEvalIterator *it = m_next_it;
        m_thread->pushIterator(it);

        // The next iterator will determine what happens next
        DEBUG_LEAVE("next - pushed new iterator");
        m_action = 0;
        m_next_it = 0;
        m_type = ModelEvalNodeT::Action;
        bool ret = it->next();

        if (ret) {
            m_action = it->action();
            m_next_it = it->iterator();
            m_type = it->type();
        }

        return ret;
    } else {
        fprintf(stdout, "Fatal Error: unknown case\n");
        return false;
    }
}

ModelEvalNodeT ModelEvaluatorSequence::type() const {
    DEBUG("type: %d", static_cast<int32_t>(m_type));
    return m_type;
}

IModelFieldAction *ModelEvaluatorSequence::action() {
    DEBUG("action: %p", m_action);
    return m_action;
}

IModelEvalIterator *ModelEvaluatorSequence::iterator() {
    DEBUG("iterator: %p", m_next_it);
    return m_next_it;
}

void ModelEvaluatorSequence::visitModelActivityParallel(IModelActivityParallel *a) {
    DEBUG_ENTER("visitModelActivityParallel");
    std::vector<ModelEvaluatorThread *>     branches;

    for (std::vector<IModelActivity *>::const_iterator
        it=a->branches().begin();
        it!=a->branches().end(); it++) {
        ModelEvaluatorThread *thread = new ModelEvaluatorThread(m_thread->randstate()->next());
        std::vector<IModelActivity *> activities;
        TaskCollectTopLevelActivities().collect(activities, *it);
        DEBUG("Branch has %d activities", activities.size());
        ModelEvaluatorSequence *seq = new ModelEvaluatorSequence(thread, activities);
        thread->pushIterator(seq);
        branches.push_back(thread);
    }

    m_next_it = new ModelEvaluatorParallel(branches);
    DEBUG_LEAVE("visitModelActivityParallel");
}

void ModelEvaluatorSequence::visitModelActivitySchedule(IModelActivitySchedule *a) {
    DEBUG_ENTER("visitModelActivitySchedule");
    DEBUG_LEAVE("visitModelActivitySchedule");
}

void ModelEvaluatorSequence::visitModelActivitySequence(IModelActivitySequence *a) {
    DEBUG_ENTER("visitModelActivitySequence");
    // Unclear if we'll really hit this...
    DEBUG_LEAVE("visitModelActivitySequence");
}

void ModelEvaluatorSequence::visitModelActivityTraverse(IModelActivityTraverse *a) {
    DEBUG_ENTER("visitModelActivityTraverse");
    IModelFieldAction *action = a->getTarget();

    DEBUG("TODO: randomize action");
    DEBUG("TODO: determine if inference is required");

    if (action->activities().size() == 1) {
        DEBUG("Single-activity compound action");
        std::vector<IModelActivity *> activities;
        TaskCollectTopLevelActivities().collect(
            activities,
            action->activities().at(0));
        ModelEvaluatorSequence *seq = new ModelEvaluatorSequence(
            m_thread, activities);
        m_next_it = seq;
    } else if (action->activities().size() > 1) {
        DEBUG("TODO: need to schedule activities");
    } else {
        DEBUG("Just a single leaf-level action");
        m_action = action;
    }

    // TODO: determine if inference is required
    // TODO: if so, perform and (possibly) push new iterator

    DEBUG_LEAVE("visitModelActivityTraverse");
}

}

