/*
 * TaskBuildComponentMap.cpp
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#include "TaskBuildComponentMap.h"
#include "TaskIsDataTypeComponent.h"

namespace arl {

TaskBuildComponentMap::TaskBuildComponentMap() {
	// TODO Auto-generated constructor stub

}

TaskBuildComponentMap::~TaskBuildComponentMap() {
	// TODO Auto-generated destructor stub
}

ComponentMap *TaskBuildComponentMap::build(vsc::IModelField *root) {
	std::vector<int32_t> parents;
	m_map = ComponentMapUP(new ComponentMap());

	int32_t id = m_map->addComponent(root);

	parents.push_back(id);

	for (auto it=root->fields().begin(); it!=root->fields().end(); it++) {
		if (TaskIsDataTypeComponent().check(it->get()->getDataType())) {
			processComponent(it->get(), parents);
		}
	}

	return m_map.release();
}

void TaskBuildComponentMap::processComponent(
		vsc::IModelField 			*comp,
		std::vector<int32_t>		parents) {
	int32_t id = m_map->addComponent(comp);

	// Add additional mappings
	for (auto it=parents.begin(); it!=parents.end(); it++) {
		m_map->addParentChildMapping(*it, id);
	}

	parents.push_back(id);
	for (auto it=comp->fields().begin(); it!=comp->fields().end(); it++) {
		if (TaskIsDataTypeComponent().check(it->get()->getDataType())) {
			processComponent(it->get(), parents);
		}
	}
	parents.pop_back();
}

} /* namespace arl */
