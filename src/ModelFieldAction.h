/*
 * ModelFieldAction.h
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeAction.h"
#include "zsp/arl/dm/IModelFieldAction.h"
#include "zsp/arl/dm/IModelActivityScope.h"
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

	virtual void accept(vsc::dm::IVisitor *v) override;


protected:
	IModelActivityScopeUP							m_activity;

};

}
}
}

