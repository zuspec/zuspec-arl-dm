/*
 * TaskBuildComponentMap.h
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelFieldComponent.h"
#include "vsc/IModelField.h"
#include "ComponentMap.h"

namespace arl {

class TaskBuildComponentMap {
public:
	TaskBuildComponentMap();

	virtual ~TaskBuildComponentMap();

	ComponentMap *build(vsc::IModelField *root);

private:

	void processComponent(
			vsc::IModelField 		*comp,
			std::vector<int32_t>	parents);


private:
	ComponentMapUP				m_map;

};

} /* namespace arl */

