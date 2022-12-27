
#include "DebugMacros.h"
#include "TaskCollectTopLevelActivities.h"

namespace zsp {
namespace arl {
namespace dm {


TaskCollectTopLevelActivities::TaskCollectTopLevelActivities() {
    DEBUG_INIT("TaskCollectTopLevelActivities");
    m_activities = 0;
}

TaskCollectTopLevelActivities::~TaskCollectTopLevelActivities() {

}

void TaskCollectTopLevelActivities::collect(
    std::vector<IModelActivity *>       &activities,
    IModelActivity                      *activity) {
    DEBUG_ENTER("collect");
    m_activities = &activities;

    activity->accept(m_this);
    DEBUG_LEAVE("collect %d", activities.size());
}

void TaskCollectTopLevelActivities::visitModelActivityParallel(IModelActivityParallel *a) {
    DEBUG_ENTER("visitModelActivityParallel");
    m_activities->push_back(a);
    DEBUG_LEAVE("visitModelActivityParallel");
}

void TaskCollectTopLevelActivities::visitModelActivitySchedule(IModelActivitySchedule *a) {
    DEBUG_ENTER("visitModelActivitySchedule");
    m_activities->push_back(a);
    DEBUG_LEAVE("visitModelActivitySchedule");
}

void TaskCollectTopLevelActivities::visitModelActivitySequence(IModelActivitySequence *a) {
    DEBUG_ENTER("visitModelActivitySequence");
    VisitorBase::visitModelActivitySequence(a);
    DEBUG_LEAVE("visitModelActivitySequence");
}

void TaskCollectTopLevelActivities::visitModelActivityTraverse(IModelActivityTraverse *a) {
    DEBUG_ENTER("visitModelActivityTraverse");
    m_activities->push_back(a);
    DEBUG_LEAVE("visitModelActivityTraverse");
}

}
}
}
