/*
 * ScheduleChoiceComponent.h
 *
 *  Created on: May 14, 2022
 *      Author: mballance
 */

#pragma once
#include "SchedulePropResultE.h"

namespace arl {

class ScheduleChoiceComponent {
public:
	ScheduleChoiceComponent();

	virtual ~ScheduleChoiceComponent();

	SchedulePropResultE propagate();

private:
	ScheduleChoiceComponent			*m_parent;

};

} /* namespace arl */

