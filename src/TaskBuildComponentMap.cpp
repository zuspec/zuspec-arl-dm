/*
 * TaskBuildComponentMap.cpp
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#include "DebugMacros.h"
#include "DataTypeComponent.h"
#include "TaskBuildComponentMap.h"
#include "TaskIsDataTypeComponent.h"

namespace arl {

TaskBuildComponentMap::TaskBuildComponentMap() {
	DEBUG_INIT("TaskBuildComponentMap");
	// TODO Auto-generated constructor stub

}

TaskBuildComponentMap::~TaskBuildComponentMap() {
	// TODO Auto-generated destructor stub
}

void TaskBuildComponentMap::build(IModelFieldComponent *root) {
	DEBUG_ENTER("build");
	m_component_s.push_back({});
	root->accept(m_this);
	m_component_s.pop_back();
	DEBUG_LEAVE("build");
}

void TaskBuildComponentMap::visitModelFieldComponent(IModelFieldComponent *f) {
	DEBUG_ENTER("visitModelFieldComponent %s %s",
		f->name().c_str(),
		f->getDataTypeT<IDataTypeComponent>()->name().c_str());

	// TODO:

	// TODO: Process binds at this level

	for (std::vector<IDataTypeAction *>::const_iterator
		it=f->getDataTypeT<DataTypeComponent>()->getActionTypes().begin();
		it!=f->getDataTypeT<DataTypeComponent>()->getActionTypes().end(); it++) {
		// Process action claims and references

	}

	// TODO: process component-type fields inside this component
	m_component_s.push_back(std::vector<IModelFieldComponent *>());
	VisitorBase::visitModelFieldComponent(f);

	// Incorporate map information from sub-components
	for (std::vector<IModelFieldComponent *>::const_iterator
		it=m_component_s.back().begin();
		it!=m_component_s.back().end(); it++) {
		f->getCompMap()->addSubComponentMap((*it)->getCompMap());
	}

	m_component_s.pop_back();

	// Need to incorporate map data from all sub-component fields
	// into this one

	m_component_s.back().push_back(f);
	DEBUG_LEAVE("visitModelFieldComponent %s %s",
		f->name().c_str(),
		f->getDataTypeT<IDataTypeComponent>()->name().c_str());
}

} /* namespace arl */
