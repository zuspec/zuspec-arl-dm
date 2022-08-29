/*
 * ModelEvaluatorParallel.cpp
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
#include "ModelEvaluatorParallel.h"
#include "ModelEvaluatorThread.h"


namespace arl {
ModelEvaluatorParallel::ModelEvaluatorParallel(
    const std::vector<ModelEvaluatorThread *> &branches) :
    m_idx(-1), m_branches(branches.begin(), branches.end()) {

}

ModelEvaluatorParallel::~ModelEvaluatorParallel() {

}

bool ModelEvaluatorParallel::next() {
    m_idx++;

    if (m_idx < m_branches.size()) {
        return true;
    } else {
        delete this;
        return false;
    }
}

ModelEvalNodeT ModelEvaluatorParallel::type() const {
    return ModelEvalNodeT::Parallel;
}

IModelFieldAction *ModelEvaluatorParallel::action() {
    return 0;
}

IModelEvalIterator *ModelEvaluatorParallel::iterator() {
    return m_branches.at(m_idx);
}

}
