/*
 * IModelActivityScope.h
 *
 *  Created on: Jun 17, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelField.h"
#include "arl/IModelActivity.h"

namespace arl {

class IModelActivityScope : public virtual vsc::IModelField, public virtual IModelActivity {
public:

	virtual ~IModelActivityScope() { }

	virtual const std::vector<IModelActivity *> &activities() const = 0;

	virtual void addActivity(IModelActivity *a, bool own=false)  = 0;

};

}
