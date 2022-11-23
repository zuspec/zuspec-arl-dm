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
#include <stdint.h>
#include <vector>
#include "arl/IModelActivitySchedule.h"
#include "arl/IModelActivityTraverse.h"

namespace arl {


class ActivityScheduleData {
public:
    ActivityScheduleData();

    virtual ~ActivityScheduleData();

public:
    struct ActionTraversalData {
        IModelActivityTraverse      *traversal;
        // TODO: need to either key context off of
        // containing context or the pool associated with
        // a given output
        int32_t                     context_action_id;

    };

    struct ScheduleRegionData {
        IModelActivitySchedule      *root;
        std::vector<int32_t>        action_ids;
        uint8_t                     *action_pairs;

        ~ScheduleRegionData();

        void init_action_pairs();

        int32_t   

    };

private:


};

}
