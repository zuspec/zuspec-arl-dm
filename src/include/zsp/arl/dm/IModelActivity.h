/*
 * IModelActivity.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <vector>
#include "vsc/IAccept.h"
#include "vsc/IModelConstraint.h"

namespace arl {

class IModelActivity;
using IModelActivityUP=std::unique_ptr<IModelActivity>;
class IModelActivity : public virtual vsc::IAccept {
public:

	virtual ~IModelActivity() { }

	virtual int32_t getNext() const = 0;

	virtual void setNext(int32_t n) = 0;

	/*
	virtual void getConstraintsLookahead(
			std::vector<vsc::IModelConstraint *> &constraints) = 0;
	 */

};


}
