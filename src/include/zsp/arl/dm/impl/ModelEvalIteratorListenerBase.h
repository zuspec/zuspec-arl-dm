/**
 * ModelEvalIteratorListenerBase.h
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
#include "zsp/arl/dm/IModelEvalIteratorListener.h"

namespace zsp {
namespace arl {
namespace dm {



class ModelEvalIteratorListenerBase : public virtual IModelEvalIteratorListener {
public:
    ModelEvalIteratorListenerBase() { }

    virtual ~ModelEvalIteratorListenerBase() { }

    virtual void enterCompoundAction(IModelFieldAction *a) override { }

    virtual void leaveCompoundAction(IModelFieldAction *a) override { }

    virtual void atomicAction(IModelFieldAction *a) override { }

    virtual void enterParallel(IModelActivityScope *p) override { }

    virtual void enterParallelBranch(IModelActivity *a) override { }

    virtual void leaveParallelBranch(IModelActivity *a) override { }

    virtual void leaveParallel(IModelActivityScope *p) override { }

    virtual void enterSequence(IModelActivityScope *a) override { }

    virtual void leaveSequence(IModelActivityScope *a) override { }

};

}
}
}


