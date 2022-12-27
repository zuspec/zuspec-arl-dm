/*
 * IModelActivitySchedule.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "zsp/arl/dm/IModelActivityScope.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelActivitySchedule : public virtual IModelActivityScope {
public:

	virtual ~IModelActivitySchedule() { }

	// TODO: Need an optional join-spec
	// Implicit (not supplied) == join_all

};

}
}
}

