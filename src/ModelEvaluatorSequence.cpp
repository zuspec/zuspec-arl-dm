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
#include "vsc/impl/PrettyPrinter.h"
#include "vsc/impl/TaskUnrollModelFieldRefConstraints.h"

#include "DebugMacros.h"
#include "ModelEvaluatorParallel.h"
#include "ModelEvaluatorSequence.h"
#include "TaskCollectTopLevelActivities.h"
#include "TaskSolveActionSet.h"


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
        m_type = ModelEvalNodeT::Action;
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

bool ModelEvaluatorSequence::valid() {
    return (m_idx >= 0 && m_idx < m_activities.size());
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
    IModelFieldComponent *comp = m_thread->component();

    for (std::vector<IModelActivity *>::const_iterator
        it=a->branches().begin();
        it!=a->branches().end(); it++) {
        ModelEvaluatorThread *thread = new ModelEvaluatorThread(
            m_thread->ctxt(), m_thread->randstate()->next());
        thread->pushComponent(comp);
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
        std::vector<vsc::IModelConstraint *> constraints;
        vsc::ICompoundSolverUP solver(m_thread->ctxt()->mkCompoundSolver());

        if (a->getWithC()) {
            constraints.push_back(a->getWithC());
        }

        // Get the active component
        IModelFieldComponent *comp_p = m_thread->component();

        TaskSolveActionSet(m_thread->ctxt(), comp_p).solve({a});

        // Add in the local action constraints
        for (std::vector<vsc::IModelConstraintUP>::const_iterator
            it=action->constraints().begin();
            it!=action->constraints().end(); it++) {
            constraints.push_back(it->get());
        }

        std::vector<IModelFieldComponent *> comp_l = comp_p->getCompMap()->getSubContexts(
            action->getDataTypeT<IDataTypeAction>()->getComponentType());
        DEBUG("NOTE: %d possible comp contexts of %s in %s", 
            comp_l.size(),
            action->getDataTypeT<IDataTypeAction>()->getComponentType()->name().c_str(),
            comp_p->name().c_str());

        std::vector<vsc::IModelField *> comp_candidates(comp_l.begin(), comp_l.end());

        vsc::ModelFieldRefConstraintDataUP comp_data(
            vsc::TaskUnrollModelFieldRefConstraints(m_thread->ctxt()).build(
                action->getFieldT<vsc::IModelFieldRef>(0),
                comp_candidates,
                {},
                constraints
            ));
        std::vector<vsc::IModelConstraint *> comp_constraints;
        for (std::vector<vsc::IModelConstraintUP>::const_iterator
            it=comp_data->getSelectConstraints().begin();
            it!=comp_data->getSelectConstraints().end(); it++) {
            if (it->get()) {
                comp_constraints.push_back(it->get());
            }
        }
        comp_constraints.push_back(comp_data->getValidC());

        for (std::vector<vsc::IModelConstraint *>::const_iterator
            it=comp_constraints.begin();
            it!=comp_constraints.end(); it++) {
            DEBUG("CompConstraint: %s", vsc::PrettyPrinter().print(*it));
        }

        bool result = solver->solve(
            m_thread->randstate(),
            {comp_data->getSelector()},
            comp_constraints,
            vsc::SolveFlags::Randomize
                | vsc::SolveFlags::RandomizeDeclRand
                | vsc::SolveFlags::RandomizeTopFields);

        fprintf(stdout, "Result: %d ; select=%lld\n",
            result, comp_data->getSelector()->val()->val_i());

        solver->solve(
            m_thread->randstate(),
            {action},
            constraints,
            vsc::SolveFlags::Randomize
                | vsc::SolveFlags::RandomizeDeclRand
                | vsc::SolveFlags::RandomizeTopFields);
        action->getFieldT<vsc::IModelFieldRef>(0)->setRef(
            comp_l.at(comp_data->getSelector()->val()->val_i()));

        m_action = action;
    }

    // TODO: determine if inference is required
    // TODO: if so, perform and (possibly) push new iterator

    DEBUG_LEAVE("visitModelActivityTraverse");
}

}

