/**
 * ModelActivityIterator.h
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
#pragma once
#include "zsp/arl/dm/impl/VisitorBase.h"
#include "zsp/arl/dm/IModelActivitySequence.h"
#include "zsp/arl/dm/IModelEvalIterator.h"

namespace zsp {
namespace arl {
namespace dm {



class ModelActivityIterator : 
    public virtual IModelEvalIterator,
    public virtual VisitorBase {
public:
    ModelActivityIterator(IModelActivityScope *scope);

    ModelActivityIterator(
        ModelEvalNodeT                  it_type,
        IModelActivityScope             *scope,
        ModelActivityIterator           *root);

    virtual ~ModelActivityIterator();

	virtual bool next() override;

	virtual bool valid() override { return m_it_idx < m_it_scope->activities().size(); }

	virtual ModelEvalNodeT type() const override { return m_next_type; }

	virtual IModelFieldAction *action() override { return m_next_action; }

	virtual IModelEvalIterator *iterator() override { return m_next_it; }

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override;

	virtual void visitModelActivityScope(IModelActivityScope *a) override;

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

    virtual void addListener(IModelEvalIteratorListener *l) override;

    virtual void remListener(IModelEvalIteratorListener *l) override;

private:
    std::vector<IModelEvalIteratorListener *>       m_listeners;
    ModelActivityIterator                           *m_root;

    // Iterator info
    ModelEvalNodeT                                  m_it_type;
    IModelActivityScope                             *m_it_scope;
    int32_t                                         m_it_idx;


    // Next-element info
    ModelEvalNodeT                                  m_next_type;
    IModelFieldAction                               *m_next_action;
    IModelActivityScope                             *m_next_scope;
    ModelActivityIterator                           *m_next_it;

};

}
}
}


