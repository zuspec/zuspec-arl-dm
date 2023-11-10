/**
 * ModelFieldComponentRoot.h
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
#include <vector>
#include "zsp/arl/dm/IModelFieldComponentRoot.h"
#include "zsp/arl/dm/IModelFieldPool.h"
#include "ModelFieldComponent.h"

namespace zsp {
namespace arl {
namespace dm {



class ModelFieldComponentRoot : 
    public virtual IModelFieldComponentRoot,
    public virtual ModelFieldComponent {
public:
    ModelFieldComponentRoot(
        IContext                *ctxt,
        const std::string       &name,
        IDataTypeComponent      *type,
        const vsc::dm::ValRef   &val);

    virtual ~ModelFieldComponentRoot();

	virtual void initCompTree() override;

    virtual const std::vector<vsc::dm::IModelField *> &getCompTypeInsts(
        IDataTypeComponent *t) const override;

    virtual const std::vector<int32_t> &getCompInstPath(
        IModelFieldComponent *comp) override;

    virtual const std::vector<IDataTypeComponent *> &getCompTypes() const override {
        return m_comp_type_l;
    }

    virtual const std::vector<int32_t> &getCompTypeSubInsts(
        IDataTypeComponent *target_t,
        IDataTypeComponent *parent_t,
        int32_t             parent_id) const override;

    virtual const std::vector<IModelFieldPool *> &getPools(vsc::dm::IDataType *t) override;

    virtual const std::vector<vsc::dm::IModelField *> &getResObjects(IDataTypeResource *res_t) override;

    virtual std::pair<int32_t, int32_t> getResPoolObjRange(IModelFieldPool *pool) override;

    virtual const std::vector<std::pair<int32_t, IModelFieldPool *>> &getClaimBoundCompPool(
        ITypeFieldClaim *claim) override;

    virtual void accept(vsc::dm::IVisitor *v) override;

    void enterComponentScope(int32_t level, int32_t idx, IModelFieldComponent *comp);

    void processBinds(IModelFieldComponent *comp);

    void leaveComponentScope(int32_t level);

    void addPool(IModelFieldPool *pool);

    void processTypeFieldRef(
        IModelFieldComponent        *comp,
        ITypeFieldInOut             *ref);

    void processTypeFieldClaim(
        IModelFieldComponent        *comp,
        ITypeFieldClaim             *claim);

private:

    using CompType2InstIdMapT=std::unordered_map<IDataTypeComponent *, std::vector<int32_t>>;
    struct CompType2InstData {
        std::vector<vsc::dm::IModelField *>         instances;
        std::vector<CompType2InstIdMapT>        subinst_m;
    };

	using CompType2InstMapT=std::unordered_map<IDataTypeComponent *, CompType2InstData>;
    using ObjType2PoolMapT=std::unordered_map<vsc::dm::IDataType *, std::vector<IModelFieldPool *>>;

    using CompInst2PathMapT=std::unordered_map<IModelFieldComponent *, std::vector<int32_t>>;

//    using CompIdPoolM=std::pair<int32_t, IModelFieldPool *>;
//	using ClaimTPoolMapT=std::unordered_map<vsc::dm::ITypeField *, std::vector<CompIdPoolM>>;

	// Holds a mapping for each component context in which this
    // field has a pool binding.
	using CompIdPoolId=std::pair<int32_t,int32_t>;
	using RefTCompPoolIdM=std::unordered_map<ITypeFieldInOut *, std::vector<CompIdPoolId>>;

    using ObjRange=std::pair<int32_t,int32_t>;
    using ResTObjectM=std::unordered_map<vsc::dm::IDataType *, std::vector<vsc::dm::IModelField *>>;
    using ResPoolObjRangeM=std::unordered_map<IModelFieldPool *, ObjRange>;

    using CompIdPoolH=std::pair<int32_t, IModelFieldPool *>;
    using ClaimCompIdPoolM=std::vector<CompIdPoolH>;
    using ClaimTCompIdPoolM=std::unordered_map<ITypeFieldClaim *, ClaimCompIdPoolM>;

    using ResourceMaxPoolSzM=std::unordered_map<vsc::dm::IDataType *, int32_t>;

private:
    static dmgr::IDebug                  *m_dbg;
    IContext                            *m_ctxt;

    int32_t                             m_init_pass;

    std::vector<IModelFieldComponent *>                      m_empty_comp_l;
    std::vector<IModelFieldPool *>                           m_empty_pool_l;
    std::vector<int32_t>                                     m_empty_int_l;
    std::vector<vsc::dm::IModelField *>                          m_empty_field_l;
    std::vector<std::pair<int32_t,int32_t>>                  m_empty_int_pair_l;
    std::vector<std::pair<int32_t, IModelFieldPool *>>       m_empty_int_pool_pair_l;

    // Holds the per-type lists of component instances within 
    // this component tree (Type -> Instances).
    CompType2InstMapT                           m_comp_type_inst_m;
    std::vector<IDataTypeComponent *>           m_comp_type_l;

    CompInst2PathMapT                           m_comp_inst_path_m;
    std::vector<int32_t>                        m_empty_path;

    // Each action has a set of potential parent-component
    // instances. The type of the action component is 
    // known. The type of the parent-action component is
    // known. Foreach parent-action component instance,
    // need to have list of valid child-action component
    // instances.
    // Map 

    // Holds the per-flow-obj lists of pools available within
    // this component tree.
    ObjType2PoolMapT                    m_obj_type_pool_m;

    // Holds the per-ref mapping between a ref-type field and the
    // valid component-id/pool-id pairs
    RefTCompPoolIdM                     m_ref_comp_pool_id_m;

    // Map from a resource type to the objects within all 
    // pools of that resource type.
    ResTObjectM                                             m_res_obj_m;

    // Map from a resource pool to 
    ResPoolObjRangeM                    m_res_pool_obj_range_m;

    // Holds the per-claim mapping between a claim-type field and
    // the value component-id/pool pairs
    ClaimTCompIdPoolM                   m_claim_comp_id_pool_m;

    /****************************************************************
     * Temporary initialization data
     * 
     * Everything below here is only used during the init process.
     * These collections are cleared after initialization is complete
     ****************************************************************/
    std::vector<CompType2InstData *>    m_inst_data_s;

    // Holds the per-type instance ID for the component
    std::vector<int32_t>                m_inst_id_s;

    // Holds the path to the current component instance through 
    // the component tree
    std::vector<int32_t>                m_inst_path;

    using TypePoolMapT=std::unordered_map<vsc::dm::IDataType *, IModelFieldPool *>;
    using FieldPoolMapT=std::unordered_map<vsc::dm::ITypeField *, IModelFieldPool *>;

    struct TypePoolMapFrame {
        TypePoolMapT                wildcard_m;
        FieldPoolMapT               field_m;
    };

    std::vector<TypePoolMapFrame>   m_type_pool_s;

};

}
}
}

