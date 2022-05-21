/*
 * ScheduleSolveActionData.h
 *
 *  Created on: May 21, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IModelField.h"
#include <memory>

namespace arl {

class ScheduleSolveActionData;
using ScheduleSolveActionDataUP=std::unique_ptr<ScheduleSolveActionData>;
class ScheduleSolveActionData {
public:
	ScheduleSolveActionData(
			vsc::IModelField		*action,
			bool					owned
			);

	virtual ~ScheduleSolveActionData();

private:
	vsc::IModelField			*m_action;
	bool						m_owned;

};

} /* namespace arl */

