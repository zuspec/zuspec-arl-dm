/*
 * IModelActivitySequence.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "zsp/arl/dm/IModelActivity.h"
#include "zsp/arl/dm/IModelActivityScope.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelActivitySequence : public virtual IModelActivityScope {
public:

	virtual ~IModelActivitySequence() { }

};

}
}
}

