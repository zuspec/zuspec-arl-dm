/**
 * TaskBuildActivitySolveModel.h
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
#include <memory>
#include <vector>
#include "arl/IContext.h"
#include "arl/impl/VisitorBase.h"
#include "vsc/impl/TaskBuildRefSelector.h"

namespace arl {

struct ResourceClaimData {
    ResourceClaimData(vsc::IDataType *t) : res_t(t) {}

    vsc::IDataType                                  *res_t;
    std::vector<std::pair<int32_t,int32_t>>         comp_sz_l;
    std::vector<vsc::IModelField *>                 resource_l;
};

struct ActivitySolveModel {
    std::vector<vsc::IModelConstraintUP>            constraints;

    using AllCompMapT=std::unordered_map<IModelFieldComponent *, uint32_t>;
    using ResTypeMapT=std::unordered_map<vsc::IDataType *, ResourceClaimData>;

    AllCompMapT                                     all_comp_m;
    std::vector<IModelFieldComponent *>             all_comp_l;
    ResTypeMapT                                     res_type_m;
    std::vector<ResourceClaimData *>                res_type_l;

    std::vector<vsc::RefSelectorUP>                 ref_l;
};
using ActivitySolveModelUP=std::unique_ptr<ActivitySolveModel>;

class TaskBuildActivitySolveModel : public VisitorBase {
public:
    TaskBuildActivitySolveModel(IContext *ctxt);

    virtual ~TaskBuildActivitySolveModel();

    ActivitySolveModel *build(
        IModelFieldComponent        *root_comp,
        IModelActivity              *root_activity);

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override;

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override;

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;


private:
    IContext                                *m_ctxt;
    ActivitySolveModelUP                    m_model;
    std::vector<IModelFieldComponent *>     m_component_s;

};

}


