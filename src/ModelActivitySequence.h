/*
 * ModelActivitySequence.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeActivity.h"
#include "arl/IModelActivitySequence.h"
#include "ModelField.h"

namespace arl {

class ModelActivitySequence : public virtual IModelActivitySequence, public ModelField {
public:
	ModelActivitySequence(
			const std::string		&name,
			IDataTypeActivity		*type);

	virtual ~ModelActivitySequence();

	virtual const std::string &name() const { return m_name; }

	virtual vsc::IDataType *getDataType() const { return m_type; }

	virtual const std::vector<IModelActivity *> &activities() const override {
		return m_activities;
	}

	virtual std::vector<IModelActivity *> &getActivities() {
		return m_activities;
	}

	virtual void addActivity(IModelActivity *a) override {
		m_activities.push_back(a);
	}

	virtual void accept(vsc::IVisitor *v) override;

private:
	std::string								m_name;
	IDataTypeActivity						*m_type;
	std::vector<IModelActivity *>			m_activities;
};

} /* namespace arl */

