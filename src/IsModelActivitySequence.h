/*
 * IsModelActivitySequence.h
 *
 *  Created on: Jun 17, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {


class IsModelActivitySequence : public VisitorBase {
public:
	IsModelActivitySequence();

	virtual ~IsModelActivitySequence();

	bool test(IModelActivity *a);

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override { }

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override { }

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override {
		m_is = true;
	}

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override { }


private:
	bool						m_is;
};

}
}
}

