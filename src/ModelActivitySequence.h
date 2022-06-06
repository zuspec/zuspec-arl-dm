/*
 * ModelActivitySequence.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelActivitySequence.h"

namespace arl {

class ModelActivitySequence : public IModelActivitySequence {
public:
	ModelActivitySequence();

	virtual ~ModelActivitySequence();

private:
	std::vector<IModelActivityUP>			m_activities;
};

} /* namespace arl */

