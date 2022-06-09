/*
 * ScheduleSolvePropagatorActivityPairRel.h
 *
 *  Created on: Jun 8, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "IScheduleSolvePropagator.h"
#include "ScheduleGraphNode.h"

namespace arl {

class ScheduleSolvePropagatorActivityPairRel;
using ScheduleSolvePropagatorActivityPairRelUP=std::unique_ptr<ScheduleSolvePropagatorActivityPairRel>;
class ScheduleSolvePropagatorActivityPairRel : public IScheduleSolvePropagator {
public:
	struct Assumption {
		ScheduleGraphNode			*src;
		ScheduleGraphNode			*dst;
		bool						is_parallel;
	};
public:
	ScheduleSolvePropagatorActivityPairRel();

	virtual ~ScheduleSolvePropagatorActivityPairRel();

	virtual bool hasNext() override;

	virtual NextResult next() override;

private:
	std::vector<Assumption>			m_assumptions;


};

} /* namespace arl */

