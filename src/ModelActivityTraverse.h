/*
 * ModelActivityTraverse.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IModelActivityTraverse.h"
#include "zsp/arl/dm/IModelFieldAction.h"
#include "ModelActivity.h"

namespace zsp {
namespace arl {
namespace dm {


class ModelActivityTraverse : 
	public virtual IModelActivityTraverse,
	public virtual ModelActivity {
public:
	ModelActivityTraverse(
			IModelFieldAction		*target,
			vsc::dm::IModelConstraint	*with_c,
			bool					own_with_c,
			IModelActivity			*activity,
			bool					owned);

	virtual ~ModelActivityTraverse();

	virtual IModelFieldAction *getTarget() const {
		return m_target;
	}

	virtual vsc::dm::IModelConstraint *getWithC() const {
		return m_with_c;
	}

	virtual IModelActivity *getActivity() const override {
		return m_activity;
	}

	virtual IModelFieldPool *getParentPool() const override {
		return m_parent_pool;
	}

	virtual void setParentPool(IModelFieldPool *p) override {
		m_parent_pool = p;
	}

	virtual bool getProcessed() const override {
		return m_processed;
	}

	virtual void setProcessed(bool p) override {
		m_processed = p;
	}

	virtual void accept(vsc::dm::IVisitor *v) override;

private:
	IModelFieldAction				*m_target;
	vsc::dm::IModelConstraint			*m_with_c;
	vsc::dm::IModelConstraintUP			m_with_c_u;
	IModelFieldPool					*m_parent_pool;
	IModelActivity					*m_activity;
	IModelActivityUP				m_activity_u;
	bool							m_processed;


};

}
}
}

