/*
 * IModelActivitySequence.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IModelActivity.h"

namespace arl {

class IModelActivitySequence : public virtual IModelActivity {
public:

	virtual ~IModelActivitySequence() { }

	virtual const std::vector<IModelActivityUP> &getActivities() const = 0;

	virtual void addActivity(IModelActivity *a) = 0;

};

}

