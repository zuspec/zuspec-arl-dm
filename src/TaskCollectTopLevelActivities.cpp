
#include "TaskCollectTopLevelActivities.h"

namespace arl {

TaskCollectTopLevelActivities::TaskCollectTopLevelActivities() {
    m_activities = 0;
}

TaskCollectTopLevelActivities::~TaskCollectTopLevelActivities() {

}

void TaskCollectTopLevelActivities::collect(
    std::vector<IModelActivity *>       &activities,
    IModelActivityScope                 *activity) {
    m_activities = &activities;

    activity->accept(m_this);
}

void TaskCollectTopLevelActivities::visitModelActivityParallel(IModelActivityParallel *a) {
    m_activities->push_back(a);
}

void TaskCollectTopLevelActivities::visitModelActivitySchedule(IModelActivitySchedule *a) {
    m_activities->push_back(a);
}

void TaskCollectTopLevelActivities::visitModelActivitySequence(IModelActivitySequence *a) {
    VisitorBase::visitModelActivitySequence(a);
}

void TaskCollectTopLevelActivities::visitModelActivityTraverse(IModelActivityTraverse *a) {
    m_activities->push_back(a);
}

}