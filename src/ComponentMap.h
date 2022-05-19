/*
 * ComponentMap.h
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "vsc/IModelField.h"

namespace arl {

class ComponentMap;
using ComponentMapUP=std::unique_ptr<ComponentMap>;
class ComponentMap {
public:
	ComponentMap();

	virtual ~ComponentMap();

	int32_t addComponent(vsc::IModelField  *c);

	void addParentChildMapping(int32_t parent, int32_t child);

	const std::unordered_set<int32_t> &getParents(int32_t child) const;

	const std::unordered_set<int32_t> &getChildren(int32_t parent) const;

	vsc::IModelField *getComponent(int32_t id) const {
		return m_components.at(id);
	}

private:
	std::vector<vsc::IModelField *>								m_components;
	std::unordered_map<int32_t, std::unordered_set<int32_t>> 	m_c2p_m;
	std::unordered_map<int32_t, std::unordered_set<int32_t>> 	m_p2c_m;
};

} /* namespace arl */

