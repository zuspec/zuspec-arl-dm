/*
 * ModelEvaluatorIncrElabParallel.cpp
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
#include "ModelEvaluatorIncrElabParallel.h"
#include "ModelEvaluatorThread.h"


namespace arl {
ModelEvaluatorIncrElabParallel::ModelEvaluatorIncrElabParallel(
    const std::vector<ModelEvaluatorThread *> &branches) :
    m_idx(-2), m_branches(branches.begin(), branches.end()) {
    DEBUG_INIT("ModelEvaluatorIncrElabParallel");
}

ModelEvaluatorIncrElabParallel::~ModelEvaluatorIncrElabParallel() {

}

bool ModelEvaluatorIncrElabParallel::next() {
    m_idx++;
    DEBUG_ENTER("next: idx=%d sz=%d", m_idx, m_branches.size());

    if (m_idx < 0 || m_idx < m_branches.size()) {
        DEBUG_LEAVE("next: ret=true");
        return true;
    } else {
        DEBUG_LEAVE("next: ret=false");
        delete this;
        return false;
    }
}

bool ModelEvaluatorIncrElabParallel::valid() {
    return (m_idx >= 0 && m_idx < m_branches.size());
}

bool ModelEvaluatorIncrElabParallel::pop() {
    // Ensure this iterator has been consumed as an iterator
    // before indicating it's time to pop
    return m_idx >= -1;
}

ModelEvalNodeT ModelEvaluatorIncrElabParallel::type() const {
    if (m_idx < 0) {
        DEBUG("type: hardcoded Parallel");
        return ModelEvalNodeT::Parallel;
    } else {
        DEBUG("type: hardcoded Sequence");
        return ModelEvalNodeT::Sequence;
    }
}

IModelFieldAction *ModelEvaluatorIncrElabParallel::action() {
    DEBUG("action: hardcoded 0");
    return 0;
}

IModelEvalIterator *ModelEvaluatorIncrElabParallel::iterator() {
    if (m_idx < 0) {
        return this;
    } else {
        DEBUG("iterator: %p", m_branches.at(m_idx));
        return m_branches.at(m_idx);
    }
}

}
