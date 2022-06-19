/*
 * ModelFieldAction.h
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeAction.h"
#include "arl/IModelFieldAction.h"
#include "arl/IModelActivityScope.h"
#include "ModelField.h"

namespace arl {

class ModelFieldAction : public virtual IModelFieldAction, public ModelField {
public:
	ModelFieldAction();

	virtual ~ModelFieldAction();

	virtual const std::vector<IModelActivityScope *> &activities() const override {
		return m_activities;
	}

	virtual void addActivity(IModelActivityScope *a) override;

	virtual void accept(vsc::IVisitor *v) override;


protected:
	std::vector<IModelActivityScope *>				m_activities;

};

} /* namespace arl */

