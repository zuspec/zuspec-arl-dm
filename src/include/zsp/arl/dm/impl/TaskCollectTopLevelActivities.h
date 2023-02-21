
#pragma once
#include "dmgr/impl/DebugMacros.h"
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {


class TaskCollectTopLevelActivities : public virtual VisitorBase {
public:

    TaskCollectTopLevelActivities() {
//        DEBUG_INIT("TaskCollectTopLevelActivities");
        m_activities = 0;
    }
    
    virtual ~TaskCollectTopLevelActivities();

    void collect(
        std::vector<IModelActivity *>   &activities,
        IModelActivity                  *activity) {
        DEBUG_ENTER("collect");
        m_activities = &activities;

        activity->accept(m_this);
        DEBUG_LEAVE("collect %d", activities.size());
    }

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override {
        DEBUG_ENTER("visitModelActivityParallel");
        m_activities->push_back(a);
        DEBUG_LEAVE("visitModelActivityParallel");
    }

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override {
        DEBUG_ENTER("visitModelActivitySchedule");
        m_activities->push_back(a);
        DEBUG_LEAVE("visitModelActivitySchedule");
    }

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override {
        DEBUG_ENTER("visitModelActivitySequence");
        VisitorBase::visitModelActivitySequence(a);
        DEBUG_LEAVE("visitModelActivitySequence");
    }

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override {
        DEBUG_ENTER("visitModelActivityTraverse");
        m_activities->push_back(a);
        DEBUG_LEAVE("visitModelActivityTraverse");
    }

private:
    static dmgr::IDebug                 *m_dbg;
    std::vector<IModelActivity *>       *m_activities;
};

dmgr::IDebug *TaskCollectTopLevelActivities::m_dbg = 0;

}
}
}
