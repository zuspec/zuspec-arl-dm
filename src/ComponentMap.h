/*
 * ComponentMap.h
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#pragma once
#include <unordered_map>
#include <unordered_set>

namespace arl {

class ComponentMap {
public:
	ComponentMap();

	virtual ~ComponentMap();

	void addChild(int32_t parent, int32_t child);

	const std::unordered_set<int32_t> &getParents(int32_t child) const;

	const std::unordered_set<int32_t> &getChildren(int32_t parent) const;

private:
	std::unordered_map<int32_t, std::unordered_set<int32_t>> m_c2p_m;
	std::unordered_map<int32_t, std::unordered_set<int32_t>> m_p2c_m;
};

} /* namespace arl */

