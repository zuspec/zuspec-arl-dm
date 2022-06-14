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

class ModelBuildContext : public virtual IModelBuildContext, public vsc::ModelBuildContext {
public:
	ModelBuildContext(IContext *ctxt);

	virtual ~ModelBuildContext();

	virtual IContext *ctxt() const override { return dynamic_cast<IContext *>(m_ctxt); }

};

} /* namespace arl */

