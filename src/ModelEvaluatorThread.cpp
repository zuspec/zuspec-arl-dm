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

ModelEvaluatorThread::ModelEvaluatorThread(vsc::IRandState *randstate) :
    m_randstate(randstate) {
    DEBUG_INIT("ModelEvaluatorThread");
}

ModelEvaluatorThread::~ModelEvaluatorThread() {

}

bool ModelEvaluatorThread::next() {
    DEBUG_ENTER("next");
    bool ret = false;
    while (m_iter_s.size()) {
        if (m_iter_s.back()->next()) {
            ret = true;
            break;
        } else {
            m_iter_s.pop_back();
        }
    }

    if (!ret) {
        delete this;
    }

    DEBUG_LEAVE("next %d", ret);
    return ret;
}

ModelEvalNodeT ModelEvaluatorThread::type() const {
    return m_iter_s.back()->type();
}

IModelFieldAction *ModelEvaluatorThread::action() {
    return m_iter_s.back()->action();
}

IModelEvalIterator *ModelEvaluatorThread::iterator() {
    return m_iter_s.back()->iterator();
}

}
