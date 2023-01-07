/*
 * ModelActivityIterator.cpp
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
#include "ModelActivityIterator.h"


namespace zsp {
namespace arl {
namespace dm {


ModelActivityIterator::ModelActivityIterator(IModelActivityScope *s) : m_scope(s) {
    m_idx = -1;
    m_action = 0;
    m_iterator = 0;
}

ModelActivityIterator::~ModelActivityIterator() {

}

bool ModelActivityIterator::next() {
    m_idx++;

    if (m_idx >= m_scope->activities().size()) {
        delete this;
        return false;
    }

    m_iterator = 0;
    m_action = 0;
    m_scope->activities().at(m_idx)->accept(m_this);

    return true;
}

void ModelActivityIterator::visitModelActivityParallel(IModelActivityParallel *a) {
    m_type = ModelEvalNodeT::Parallel;
    m_iterator = new ModelActivityIterator(a);
}

void ModelActivityIterator::visitModelActivityScope(IModelActivityScope *a) {
    if (a->getType() == ModelActivityScopeT::Parallel) {
        m_type = ModelEvalNodeT::Parallel;
        m_iterator = new ModelActivityIterator(a);
    } else {
        m_type = ModelEvalNodeT::Sequence;
        m_iterator = new ModelActivityIterator(a);
    }
}

void ModelActivityIterator::visitModelActivitySequence(IModelActivitySequence *a) {
    m_type = ModelEvalNodeT::Sequence;
    m_iterator = new ModelActivityIterator(a);
}

void ModelActivityIterator::visitModelActivityTraverse(IModelActivityTraverse *a) {
    m_type = ModelEvalNodeT::Action;
    m_action = a->getTarget();

    if (a->getTarget()->isCompound()) {
        m_iterator = new ModelActivityIterator(a->getTarget()->getActivity());
    }
}

}
}
}
