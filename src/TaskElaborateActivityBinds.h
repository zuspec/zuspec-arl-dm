/**
 * TaskElaborateActivityBinds.h
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
#include "arl/IContext.h"
#include "arl/impl/VisitorBase.h"
#include "ActivityScheduleData.h"

namespace arl {

class TaskElaborateActivityBinds : public VisitorBase {
public:
    TaskElaborateActivityBinds(IContext *ctxt);

    virtual ~TaskElaborateActivityBinds();

    bool elab(
        ActivityScheduleData    *sched_data,
        IModelActivity          *activity);

	virtual void visitModelActivityBind(IModelActivityBind *a) override;

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override;

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override;

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override;

	virtual void visitModelActivityScope(IModelActivityScope *a) override;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

protected:
    void processClaim(IModelFieldClaim *f);

    void processRefInput(IModelFieldInOut *f);

    void processRefOutput(IModelFieldInOut *f);

    void processActivityParallel(IModelActivityScope *a);

    void processActivitySchedule(IModelActivityScope *a);

    void processActivitySequence(IModelActivityScope *a);

private:
    struct ResourceClaimType {
        std::vector<vsc::IRefSelector *>        lock;
        std::vector<vsc::IRefSelector *>        share;
    };

    struct ResourceClaimM {
        std::unordered_map<vsc::IDataType *, ResourceClaimType>     claims;
        std::vector<vsc::IDataType *>                               types;
    };
    using ResourceClaimMUP=std::unique_ptr<ResourceClaimM>;

    using ResourceContentionSet=std::vector<ResourceClaimM>;

private:
    void propagateResources(
        ResourceClaimM              &dst,
        const ResourceClaimM        &src);

private:
    static vsc::IDebug                                              *m_dbg;
    IContext                                                        *m_ctxt;
    ActivityScheduleData                                            *m_sched_data;

//    std::vector<IModelActivityTraverse *>                           m_traverse_s;

    std::vector<ActivityScheduleData::ActionTraversalData *>        m_traverse_s;
    std::vector<ActivityScheduleData::ScheduleRegionData *>         m_schedule_s;
    std::vector<ResourceClaimM>                                   m_resource_s;



    // TODO: must capture condition(s) (if any) for current actions

    // TODO: must capture binds and any conditions on those binds


};

}


