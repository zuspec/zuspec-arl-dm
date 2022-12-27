/*
 * ModelBuildContext.h
 *
 *  Created on: Jun 12, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IModelBuildContext.h"
#include "vsc/dm/impl/ModelBuildContext.h"
#include "vsc/dm/IModelField.h"
#include <vector>

namespace zsp {
namespace arl {
namespace dm {


class ModelBuildContext : public virtual IModelBuildContext, public virtual vsc::dm::ModelBuildContext {
public:
	ModelBuildContext(IContext *ctxt) : vsc::dm::ModelBuildContext(ctxt) { }

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

}
}
}

