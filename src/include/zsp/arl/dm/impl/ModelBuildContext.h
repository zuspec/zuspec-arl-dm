/*
 * ModelBuildContext.h
 *
 *  Created on: Jun 12, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelBuildContext.h"
#include "vsc/impl/ModelBuildContext.h"
#include "vsc/IModelField.h"
#include <vector>

namespace arl {

class ModelBuildContext : public virtual IModelBuildContext, public virtual vsc::ModelBuildContext {
public:
	ModelBuildContext(IContext *ctxt) : vsc::ModelBuildContext(ctxt) { }

	virtual ~ModelBuildContext() { }

	virtual void pushActivityScope(IModelActivityScope *a) override {
		m_activity_scope_s.push_back(a);
	}

	virtual IModelActivityScope *getActivityScope() override {
		return (m_activity_scope_s.size())?m_activity_scope_s.back():0;
	}

	virtual IModelActivityScope *popActivityScope() override {
		IModelActivityScope *ret = getActivityScope();
		if (ret) {
			m_activity_scope_s.pop_back();
		}
		return ret;
	}

	virtual IContext *ctxt() const override { return dynamic_cast<IContext *>(m_ctxt); }

protected:

	std::vector<IModelActivityScope *>			m_activity_scope_s;

};

} /* namespace arl */

