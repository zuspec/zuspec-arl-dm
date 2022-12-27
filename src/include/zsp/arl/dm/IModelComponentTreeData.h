/**
 * IModelComponentTreeData.h
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
#include <vector>
#include "zsp/arl/dm/IDataTypeComponent.h"

namespace zsp {
namespace arl {
namespace dm {




class IModelComponentTreeData {
public:

    virtual ~IModelComponentTreeData() { }

    virtual const std::vector<vsc::dm::IModelField *> &getCompTypeInsts(
        IDataTypeComponent *t) const = 0;

    virtual const std::vector<IDataTypeComponent *> &getCompTypes() const = 0;

    /**
     * @brief Get a list of instances of target_t in parent context 'id'
     * 
     * @param target_t  - Component type of interest
     * @param parent_t  - Parent component type
     * @param parent_id - Parent instance id
     * @return * const std::vector<int32_t>& 
     * 
     */
    virtual const std::vector<int32_t> &getCompTypeSubInsts(
        IDataTypeComponent *target_t,
        IDataTypeComponent *parent_t,
        int32_t             parent_id) const = 0;

    virtual const std::vector<IModelFieldPool *> &getPools(vsc::dm::IDataType *t) = 0;

    /**
     * @brief Returns aggregated list of resource objects for a given type
     * 
     * @param res_t 
     * @return const std::vector<vsc::dm::IModelField *>& 
     */
    virtual const std::vector<vsc::dm::IModelField *> &getResObjects(IDataTypeResource *res_t) = 0;

    /**
     * @brief Returns the range of objects associated with the specified pool
     * 
     * @param pool 
     * @return const std::vector<std::pair<int32_t, int32_t>>& 
     */
    virtual std::pair<int32_t, int32_t> getResPoolObjRange(IModelFieldPool *pool) = 0;

    /**
     * @brief Returns the list of per-context bindings for the specified claim type
     * 
     * @param claim 
     * @return std::pair<int32_t, IModelFieldPool *> 
     */
    virtual const std::vector<std::pair<int32_t, IModelFieldPool *>> &getClaimBoundCompPool(
        ITypeFieldClaim *claim) = 0;

};

}
}
}


