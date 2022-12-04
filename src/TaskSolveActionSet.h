/**
 * TaskSolveActionSet.h
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
#include <unordered_map>
#include "arl/IContext.h"
#include "arl/IModelActivityTraverse.h"
#include "arl/IModelEvalIterator.h"
#include "arl/IModelFieldComponent.h"
#include "arl/impl/VisitorBase.h"

namespace vsc {
    class ModelFieldRefConstraintData;
    using ModelFieldRefConstraintDataUP=std::unique_ptr<ModelFieldRefConstraintData>;
}

namespace arl {


class TaskSolveActionSet : public VisitorBase {
public:
    TaskSolveActionSet(
        IContext                *ctxt,
        vsc::IRandState         *randstate,
        IModelFieldComponent    *comp);

    virtual ~TaskSolveActionSet();

    // TODO: need to pass in bind info?
    bool solve(const std::vector<IModelActivityTraverse *> &traversals);

	virtual void visitModelFieldRef(vsc::IModelFieldRef *f) override;

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) override;

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) override;

private:
    void build_comp_map(const std::vector<IModelActivityTraverse *> &traversals);

    void build_resource_constraints(
        std::vector<vsc::IModelConstraintUP> &constraints);

private:

    using RefSelPairT=std::pair<vsc::IModelFieldRef *, vsc::ModelFieldRefConstraintDataUP>;

    struct ActionData {
        ActionData(IModelActivityTraverse *t) : m_traversal(t) {} 
        IModelActivityTraverse                              *m_traversal;
        std::vector<uint32_t>                               m_comp_ctxt_l;
    };

    struct ResourceClaimData {

        ResourceClaimData(vsc::IDataType *t) : m_res_t(t) {}
        vsc::IDataType                              *m_res_t;
        std::vector<std::pair<int32_t,int32_t>>     m_comp_sz_l;
        std::vector<vsc::IModelField *>             m_resource_l;
        std::vector<vsc::IRefSelector *>            m_lock_claims;
        std::vector<vsc::IRefSelector *>            m_share_claims;
    };

    using AllCompMapT=std::unordered_map<IModelFieldComponent *,uint32_t>;
    using ResTypeMapT=std::unordered_map<vsc::IDataType *, ResourceClaimData>;


private:
    static vsc::IDebug                                      *m_dbg;
    IContext                                                *m_ctxt;
    vsc::IRandState                                         *m_randstate;
    IModelFieldComponent                                    *m_comp;
    AllCompMapT                                              m_all_comp_m;
    std::vector<IModelFieldComponent *>                      m_all_comp_l;
    ActionData                                              *m_action_data;
    std::vector<ActionData>                                  m_action_data_l;
    ResTypeMapT                                             m_res_type_m;
    std::vector<ResourceClaimData *>                        m_res_type_l;
    std::vector<vsc::IRefSelectorUP>                        m_ref_l;

//    std::unordered_map<vsc::IDataTy
    std::vector<IModelEvalIteratorUP>                       m_result;
    std::vector<vsc::IModelConstraint *>                    m_constraints;

};

}

