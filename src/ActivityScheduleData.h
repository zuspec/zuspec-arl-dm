/**
 * ActivityScheduleData.h
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
#include <stdint.h>
#include <unordered_map>
#include <vector>
#include "arl/IContext.h"
#include "arl/IModelComponentTreeData.h"
#include "arl/IModelActivitySchedule.h"
#include "arl/IModelActivityTraverse.h"
#include "vsc/IRefSelector.h"
#include "vsc/impl/TaskUnrollModelFieldRefConstraints.h"

namespace arl {

class ActivityScheduleData;
using ActivityScheduleDataUP=std::unique_ptr<ActivityScheduleData>;
class ActivityScheduleData {
public:
    struct ActionTraversalData;
    struct ActionData;
    struct ClaimData;
public:
    ActivityScheduleData(
        IContext                    *ctxt,
        IModelComponentTreeData     *comp_data);

    virtual ~ActivityScheduleData();

    void initRefSelectors();

    void getSelectorsConstraints(
        std::vector<vsc::IRefSelector *>        &refs,
        std::vector<vsc::IModelConstraint *>    &constraints);

    ActionTraversalData *getTraversal(IModelActivityTraverse *t);

    ActionTraversalData *addTraversal(
        IModelFieldAction           *parent,
        IModelActivityTraverse      *traversal,
        vsc::IModelExpr             *cond
        );

    vsc::IRefSelector *getRefSelector(vsc::IModelFieldRef *ref);

    vsc::IRefSelector *addRefSelector(
        vsc::IModelFieldRef         *ref,
        FlowObjKindE                kind);

    int32_t getFlowObjId(
        vsc::IModelField        *obj);

    int32_t addFlowObj(
        vsc::IModelField        *obj);

    // Holds backtrack information
    struct CheckPoint {

    };

    CheckPoint checkpoint();

    void restore(const CheckPoint &cp);

    ActivityScheduleData::ClaimData *getClaim(
        ActivityScheduleData::ActionData    *action,
        IModelFieldClaim                    *f);

    void addConstraint(vsc::IModelConstraint *c);

public:

    // ClaimData bundles the selector for a specific resource claim
    // with constraints specific to this claim and the action 
    // to which it applies.
    struct ClaimData;
    using ClaimDataUP=std::unique_ptr<ClaimData>;
    struct ClaimData {
        vsc::IRefSelectorUP                                     selector;
        std::vector<vsc::IModelConstraintUP>                    constraints;
    };

    // Each action requires a set of information centering
    // around its components and claims
    // There may be a many:one relationship between traversals
    // and actions
    using ActionDataUP=std::unique_ptr<ActionData>;
    struct ActionData {
        // Track which traversals reference this action and
        // under what circumstances
        IModelFieldAction                                       *action;

        // Note: if two unconditional traversals point to the
        // same action, then we have a conflict
        std::vector<ActionTraversalData *>                      traversals;

        vsc::IRefSelectorUP                                     comp_ref_sel;

        // Need a set of ref selectors to cover resources
        std::unordered_map<IModelFieldClaim *,ClaimDataUP>      claim_m;
        std::vector<ClaimData *>                                claim_l;

        // Do we need to qualify/catergorize these?
        std::vector<vsc::IModelConstraintUP>                    constraints;

        ClaimData *getClaim(IModelFieldClaim *f);
    };

    // There
    using ActionTraversalDataUP=std::unique_ptr<ActionTraversalData>;
    struct ActionTraversalData {
        IModelActivityTraverse          *traversal;

        // 
        vsc::IModelExprUP               m_cond;

        // Action <key I/O> is connected to a pool.
        // Action comp must match this.
        // 
        // TODO: need to either key context off of
        // containing context or the pool associated with
        // a given output
        int32_t                         context_action_id;

        ActionData                      *action;
    };

    struct ScheduleRegionData {
        IModelActivitySchedule      *root;
        std::vector<int32_t>        action_ids;
        uint8_t                     *action_pairs;

        ~ScheduleRegionData();

        void init_action_pairs();

    };

private:
    struct ObjData {
        std::unordered_map<vsc::IModelField *, int32_t>     obj2id_m;
        std::vector<vsc::IModelField *>                     obj_l;
    };
    using FlowObjTypeM=std::unordered_map<vsc::IDataType *, ObjData>;

private:
    static vsc::IDebug                                              *m_dbg;
    IContext                                                        *m_ctxt;
    IModelComponentTreeData                                         *m_comp_data;
    std::unordered_map<IModelActivityTraverse *, int32_t>           m_traversal_id_m;
    std::vector<ActionTraversalDataUP>                              m_traversal_l;

    std::unordered_map<IModelFieldAction *, int32_t>                m_action_id_m;
    std::vector<ActionDataUP>                                       m_action_l;

    std::unordered_map<vsc::IModelFieldRef *, vsc::IRefSelectorUP>  m_ref_selector_m;
    std::vector<vsc::IRefSelector *>                                m_buffer_sel_l;
    std::vector<vsc::IRefSelector *>                                m_resource_sel_l;
    std::vector<vsc::IRefSelector *>                                m_stream_sel_l;

    FlowObjTypeM                                                    m_objtype_m;
    std::vector<vsc::IModelConstraintUP>                            m_constraints;

    // Need a selector per action to handle the 


};

}
