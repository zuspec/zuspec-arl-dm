/*
 * TaskBuildComponentMap.h
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelFieldComponent.h"
#include "arl/impl/VisitorBase.h"
#include "vsc/IModelField.h"
#include "ComponentMap.h"

namespace arl {

class TaskBuildComponentMap : public virtual VisitorBase {
public:
	TaskBuildComponentMap();

	virtual ~TaskBuildComponentMap();

	void build(IModelFieldComponent *root);

	virtual void visitModelFieldComponent(IModelFieldComponent *f) override;

private:

private:
	std::vector<std::vector<IModelFieldComponent *>>		m_component_s;

};

} /* namespace arl */

