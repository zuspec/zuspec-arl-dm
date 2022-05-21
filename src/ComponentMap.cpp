/*
 * ComponentMap.cpp
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#include "ComponentMap.h"

namespace arl {

ComponentMap::ComponentMap() {
	// TODO Auto-generated constructor stub

}

ComponentMap::~ComponentMap() {
	// TODO Auto-generated destructor stub
}

int32_t ComponentMap::addComponent(vsc::IModelField *comp) {
	int32_t id = m_components.size();
	m_components.push_back(comp);

	auto t2i_it = m_t2i_m.find(comp->getDataType());

	if (t2i_it != m_t2i_m.end()) {
		t2i_it->second.insert(id);
	} else {
		m_t2i_m.insert({comp->getDataType(), {id}});
	}

	return id;
}

void ComponentMap::addParentChildMapping(int32_t parent, int32_t child) {
	auto c2p_it = m_c2p_m.find(child);

	if (c2p_it != m_c2p_m.end()) {
		c2p_it->second.insert(parent);
	} else {
		m_c2p_m.insert({child, {parent}});
	}

	auto p2c_it = m_p2c_m.find(parent);

	if (p2c_it != m_p2c_m.end()) {
		p2c_it->second.insert(child);
	} else {
		m_p2c_m.insert({parent, {child}});
	}
}

const std::unordered_set<int32_t> &ComponentMap::getParents(int32_t child) const {
	return m_c2p_m.find(child)->second;
}

const std::unordered_set<int32_t> &ComponentMap::getChildren(int32_t parent) const {
	return m_p2c_m.find(parent)->second;
}

const std::unordered_set<int32_t> &ComponentMap::getTypeInsts(vsc::IDataType *t) const {
	return m_t2i_m.find(t)->second;
}

} /* namespace arl */
