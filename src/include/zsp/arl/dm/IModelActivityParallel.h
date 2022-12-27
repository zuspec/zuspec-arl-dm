/*
 * IModelActivityParallel.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include <string>
#include <vector>
#include "zsp/arl/dm/IModelActivityScope.h"
#include "vsc/dm/IModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelActivityParallel;
using IModelActivityParallelUP=std::unique_ptr<IModelActivityParallel>;
class IModelActivityParallel : 
	public virtual IModelActivityScope, 
	public virtual vsc::dm::IModelField {
public:

	virtual ~IModelActivityParallel() { }

	virtual const std::vector<IModelActivity *> &branches() const = 0;

	virtual void addBranch(IModelActivity *a) = 0;

	// TODO: Need an optional join-spec
	// Implicit (not supplied) == join_all


};

}
}
}

