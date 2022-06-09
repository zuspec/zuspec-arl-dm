/*
 * ScheduleSolveProblem.h
 *
 *  Created on: May 21, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include <unordered_map>
#include "ScheduleSolveActionData.h"
#include "ScheduleSolvePropagatorActivityPairRel.h"

namespace arl {

class ScheduleSolveProblem;
using ScheduleSolveProblemUP=std::unique_ptr<ScheduleSolveProblem>;

/**
 * Represents the ensire scheduling problem wrt actions
 */
class ScheduleSolveProblem {
public:
	ScheduleSolveProblem();

	virtual ~ScheduleSolveProblem();

	ScheduleSolveActionData *addActivity(IModelActivity *activity);

	void addRelation(
			IModelActivity		*src,
			IModelActivity		*dst,
			bool				is_parallel);

private:
	struct pair_hash {
		template <class T1, class T2> std::size_t operator()(const std::pair<T1,T2> &p) const {
			return std::hash<T1>()(p.first) ^ std::hash<T2>()(p.second);
		}
	};
	using RelPairKeyT=std::pair<IModelActivity*,IModelActivity*>;
	using RelPairMapT=std::unordered_map<RelPairKeyT,ScheduleSolvePropagatorActivityPairRel*,pair_hash>;

private:
	std::vector<ScheduleSolvePropagatorActivityPairRelUP>	m_rel_assumptions;
	RelPairMapT												m_rel_m;
	std::vector<ScheduleSolveActionDataUP>					m_actions;
};

} /* namespace arl */

