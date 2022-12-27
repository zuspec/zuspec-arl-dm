/*
 * ModelActivitySequence.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeActivity.h"
#include "zsp/arl/dm/IModelActivitySequence.h"
#include "ModelActivityScope.h"
#include "ModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class ModelActivitySequence : 
	public virtual IModelActivitySequence, 
	public virtual ModelActivityScope {
public:
	ModelActivitySequence(
			const std::string		&name,
			IDataTypeActivity		*type);

	virtual ~ModelActivitySequence();

	virtual ModelActivityScopeT getType() const override {
		return ModelActivityScopeT::Sequence;
	}

	virtual void setType(ModelActivityScopeT t) override { }

	virtual const std::string &name() const { return m_name; }

	virtual vsc::dm::IDataType *getDataType() const { return m_type; }

	virtual const std::vector<IModelActivity *> &activities() const override {
		return m_activities;
	}

	virtual std::vector<IModelActivity *> &getActivities() {
		return m_activities;
	}

	virtual void addActivity(IModelActivity *a, bool own) override;

	virtual void accept(vsc::dm::IVisitor *v) override;

private:
	std::string								m_name;
	IDataTypeActivity						*m_type;
	std::vector<IModelActivity *>			m_activities;
	std::vector<IModelActivityUP>			m_activities_up;
};

}
}
}

