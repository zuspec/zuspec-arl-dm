/**
 * TaskPopulateResourcePools.h
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
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {



class TaskPopulateResourcePools : public virtual VisitorBase {
public:
    TaskPopulateResourcePools(IContext *ctxt);

    virtual ~TaskPopulateResourcePools();

    void populate(IModelFieldComponent *root);

	virtual void visitModelFieldComponent(IModelFieldComponent *f) override;

	virtual void visitModelFieldPool(IModelFieldPool *f) override;

	virtual void visitDataTypeResource(IDataTypeResource *t) override;

private:
    IContext                            *m_ctxt;
    IModelFieldPool                     *m_pool;
};

}
}
}

