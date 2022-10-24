/**
 * TaskBuildActivityComponentMap.h
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
#include <unordered_map>
#include <vector>
#include "arl/IModelActivity.h"
#include "arl/IModelFieldAction.h"
#include "arl/IModelFieldComponent.h"
#include "arl/impl/VisitorBase.h"

namespace arl {

struct ActivityComponentMap {

    using AllCompMapT=std::unordered_map<IModelFieldComponent *, uint32_t>;

    AllCompMapT                         all_comp_m;
    std::vector<IModelFieldComponent *> all_comp_l;
};
using ActivityComponentMapUP=std::unique_ptr<ActivityComponentMap>;


class TaskBuildActivityComponentMap : public VisitorBase {
public:
    TaskBuildActivityComponentMap(IModelFieldComponent *root_comp);

    virtual ~TaskBuildActivityComponentMap();

    ActivityComponentMap *build(IModelActivity *root_activity);

private:
    IModelFieldComponent                *m_root_comp;

};

}


