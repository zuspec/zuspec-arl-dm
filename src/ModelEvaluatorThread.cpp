/*
 * ModelEvaluatorThread.cpp
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
#include "ModelEvaluatorThread.h"

namespace arl {

ModelEvaluatorThread::ModelEvaluatorThread(
    IContext            *ctxt,
    vsc::IRandState     *randstate) : m_ctxt(ctxt), m_randstate(randstate) {
    DEBUG_INIT("ModelEvaluatorThread");
}

ModelEvaluatorThread::~ModelEvaluatorThread() {

}

bool ModelEvaluatorThread::next() {
    DEBUG_ENTER("next m_iter_s.size=%d", m_iter_s.size());
    bool ret = false;

    // First, get rid of any entries that have expired
    while (m_iter_s.size() && m_iter_s.back()->pop()) {
        DEBUG("pop element");
        m_iter_s.pop_back();
    }

    while (!ret && m_iter_s.size()) {
        if (m_iter_s.back()->next()) {
            ret = true;
        } else {
            DEBUG("pop last iterator");
            m_iter_s.pop_back();
        }
    }

    if (!ret) {
        delete this;
    }

    DEBUG_LEAVE("next %d", ret);
    return ret;
}

bool ModelEvaluatorThread::valid() {
    return (m_iter_s.size() && m_iter_s.back()->valid());
}

ModelEvalNodeT ModelEvaluatorThread::type() const {
    DEBUG("type");
    return m_iter_s.back()->type();
}

IModelFieldAction *ModelEvaluatorThread::action() {
    DEBUG("action");
    return m_iter_s.back()->action();
}

IModelEvalIterator *ModelEvaluatorThread::iterator() {
    DEBUG("iterator");
    return m_iter_s.back()->iterator();
}

void ModelEvaluatorThread::pushIterator(IModelEvalIterator *it) {
    m_iter_s.push_back(it);
}

void ModelEvaluatorThread::pushComponent(IModelFieldComponent *comp) {
    m_component_s.push_back(comp);
}

void ModelEvaluatorThread::popComponent() {
    m_component_s.pop_back();
}

}
