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
#include <algorithm>
#include "ModelActivityIterator.h"


namespace zsp {
namespace arl {
namespace dm {


ModelActivityIterator::ModelActivityIterator(IModelActivityScope *scope) :
    m_it_scope(scope), m_root(this) {
    m_it_idx = -1;

    m_next_action = 0;
    m_next_it = 0;
}

ModelActivityIterator::ModelActivityIterator(
    ModelEvalNodeT              it_type,
    IModelActivityScope         *scope,
    ModelActivityIterator       *root) :
    m_it_type(it_type), m_it_scope(scope), m_it_idx(-1),
    m_root(root) {
    
}

ModelActivityIterator::~ModelActivityIterator() {

}

bool ModelActivityIterator::next() {
    m_it_idx++;

    if (m_it_idx > 0) {
        // Handle end-events (if needed)
        for (std::vector<IModelEvalIteratorListener *>::const_iterator
            it=m_root->m_listeners.begin();
            it!=m_root->m_listeners.end(); it++) {
            if (m_it_type == ModelEvalNodeT::Parallel) {
                (*it)->leaveParallelBranch(0);
            } else {
                switch (m_next_type) {
                    case ModelEvalNodeT::Action: {
                        if (m_next_action->isCompound()) {
                            (*it)->leaveCompoundAction(m_next_action);
                        }
                    } break;
                    case ModelEvalNodeT::Parallel: {
                        (*it)->leaveParallel(m_next_scope);
                    } break;
                    case ModelEvalNodeT::Sequence: {
                        (*it)->leaveSequence(m_next_scope);
                    }
                }

            }
        }
    }

    if (m_it_idx >= m_it_scope->activities().size()) {
        delete this;
        return false;
    }

    m_next_it = 0;
    m_next_action = 0;
    m_next_scope = 0;
    m_it_scope->activities().at(m_it_idx)->accept(m_this);

    // Handle begin event
    for (std::vector<IModelEvalIteratorListener *>::const_iterator
        it=m_root->m_listeners.begin();
        it!=m_root->m_listeners.end(); it++) {

        switch (m_next_type) {
            case ModelEvalNodeT::Action: {
                if (m_next_action->isCompound()) {
                    (*it)->enterCompoundAction(m_next_action);
                } else {
                    (*it)->atomicAction(m_next_action);
                }
            } break;
            case ModelEvalNodeT::Parallel: {
                (*it)->enterParallel(m_next_scope);
            } break;
            case ModelEvalNodeT::Sequence: {
                (*it)->enterSequence(m_next_scope);
            } break;
        }
    }

    return true;
}

void ModelActivityIterator::visitModelActivityParallel(IModelActivityParallel *a) {
    m_next_type = ModelEvalNodeT::Parallel;
    m_next_it = new ModelActivityIterator(ModelEvalNodeT::Parallel, a, m_root);
}

void ModelActivityIterator::visitModelActivityScope(IModelActivityScope *a) {
    m_next_scope = a;
    if (a->getType() == ModelActivityScopeT::Parallel) {
        m_next_type = ModelEvalNodeT::Parallel;
        m_next_it = new ModelActivityIterator(ModelEvalNodeT::Parallel, a, m_root);
    } else {
        m_next_type = ModelEvalNodeT::Sequence;
        m_next_it = new ModelActivityIterator(ModelEvalNodeT::Sequence, a, m_root);
    }
}

void ModelActivityIterator::visitModelActivitySequence(IModelActivitySequence *a) {
    m_next_type = ModelEvalNodeT::Sequence;
    m_next_scope = a;
    m_next_it = new ModelActivityIterator(ModelEvalNodeT::Sequence, a, m_root);
}

void ModelActivityIterator::visitModelActivityTraverse(IModelActivityTraverse *a) {
    m_next_type = ModelEvalNodeT::Action;
    m_next_action = a->getTarget();

    if (a->getTarget()->isCompound()) {
        m_next_it = new ModelActivityIterator(
            ModelEvalNodeT::Sequence, 
            a->getTarget()->getActivity(), 
            m_root);
    }
}

void ModelActivityIterator::addListener(IModelEvalIteratorListener *l) {
    m_root->m_listeners.push_back(l);
}

void ModelActivityIterator::remListener(IModelEvalIteratorListener *l) {
    std::vector<IModelEvalIteratorListener *>::iterator it;
    
    if ((it=std::find(m_listeners.begin(), m_listeners.end(), l)) != m_listeners.end()) {
        m_listeners.erase(it);
    }
}

}
}
}
