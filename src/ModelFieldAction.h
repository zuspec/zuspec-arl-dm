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

namespace zsp {
namespace arl {
namespace dm {


class ModelFieldAction : 
	public virtual IModelFieldAction, 
	public virtual ModelField {
public:
	ModelFieldAction();

	virtual ~ModelFieldAction();

	virtual bool isCompound() const override {
		return getActivity();
	}

	virtual IModelActivityScope *getActivity() const override {
		return m_activity.get();
	}

	virtual void setActivity(IModelActivityScope *a) override {
		m_activity = IModelActivityScopeUP(a);
	}

	virtual void accept(vsc::IVisitor *v) override;


protected:
	IModelActivityScopeUP							m_activity;

};

}
}
}

