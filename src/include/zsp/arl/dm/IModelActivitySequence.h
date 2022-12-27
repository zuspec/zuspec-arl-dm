/*
 * IModelActivitySequence.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IModelActivity.h"
#include "arl/IModelActivityScope.h"

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

