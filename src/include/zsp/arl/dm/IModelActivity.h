/*
 * IModelActivity.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <vector>
#include "vsc/dm/IAccept.h"
#include "vsc/dm/IModelConstraint.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelActivity;
using IModelActivityUP=std::unique_ptr<IModelActivity>;
class IModelActivity : public virtual vsc::dm::IAccept {
public:

	virtual ~IModelActivity() { }

	virtual int32_t getNext() const = 0;

	virtual void setNext(int32_t n) = 0;

	/*
	virtual void getConstraintsLookahead(
			std::vector<vsc::dm::IModelConstraint *> &constraints) = 0;
	 */

};

}
}
}
