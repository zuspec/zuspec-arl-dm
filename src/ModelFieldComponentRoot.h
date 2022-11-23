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
#include "ModelFieldComponent.h"

namespace arl {


class ModelFieldComponentRoot : 
    public virtual ModelFieldComponent,
    public virtual ModelField {
public:
    ModelFieldComponentRoot(
        IContext            *ctxt,
        const std::string   &name,
        IDataTypeComponent  *type);

    virtual ~ModelFieldComponentRoot();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual vsc::IDataType *getDataType() const override {
        return m_type;
    }

private:
	using CompType2InstMapT=std::unordered_map<IDataTypeComponent *, std::vector<IModelFieldComponent *>>;
    using ObjType2PoolMapT=std::unordered_map<vsc::IDataType *, std::vector<IModelFieldPool *>>;
	using ClaimRef2PoolMapT=std::unordered_map<vsc::ITypeField *, IModelFieldPool *>;

	// Holds a mapping between component id and pool id
	using CompIdPoolId=std::pair<int32_t,int32_t>;
	using RefTCompPoolIdM=std::unordered_map<ITypeFieldInOut *, std::vector<CompIdPoolId>>;

private:
    std::string                         m_name;

    // Holds the per-type lists of component instances within 
    // this component tree.
    CompType2InstMapT                   m_comp_type_inst_m;

    // Holds the per-flow-obj lists of pools available with
    // this component tree.
    ObjType2PoolMapT                    m_obj_type_pool_m;

    // Holds the per-ref mapping between a ref-type field and the
    // valid component-id/pool-id pairs
    RefTCompPoolIdM                     m_ref_comp_pool_id_m;

    IDataTypeComponent                  *m_type;

};

}

