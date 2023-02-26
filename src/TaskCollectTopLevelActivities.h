
#pragma once
#include "zsp/arl/dm/impl/TaskCollectTopLevelActivities.h"
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {


class TaskCollectTopLevelActivities : public virtual VisitorBase {
public:

    TaskCollectTopLevelActivities();
    
    virtual ~TaskCollectTopLevelActivities();

    void collect(
        std::vector<IModelActivity *>   &activities,
        IModelActivity                  *activity
    );

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override;

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override;

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override;

private:
    std::vector<IModelActivity *>       *m_activities;
};

}
}
}
