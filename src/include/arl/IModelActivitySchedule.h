/*
 * IModelActivitySchedule.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IModelActivity.h"

namespace arl {

class IModelActivitySchedule : public virtual IModelActivity {
public:

	virtual ~IModelActivitySchedule() { }

	virtual const std::vector<IModelActivityUP> &getActivities() const = 0;

	virtual void addActivity(IModelActivity *a) = 0;

	// TODO: Need an optional join-spec
	// Implicit (not supplied) == join_all

};

}

