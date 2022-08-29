/*
 * ModelFieldComponent.h
 *
 *  Created on: May 17, 2022
 *      Author: mballance
 */

#pragma once
#include <stdint.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "arl/IContext.h"
#include "arl/IDataTypeComponent.h"
#include "arl/IModelFieldComponent.h"
#include "vsc/IModelField.h"
#include "vsc/IModelVal.h"
#include "ComponentMap.h"
#include "ModelField.h"

namespace arl {

class ModelFieldComponent : 
	public virtual IModelFieldComponent,
	public virtual ModelField {
public:
	ModelFieldComponent(
			arl::IContext			*ctxt,
			const std::string 		&name,
			vsc::IDataType			*type);

	virtual ~ModelFieldComponent();

	virtual void initCompTree() override;

	virtual void accept(vsc::IVisitor *v) override;

private:
	using CompTCompInstM=std::unordered_map<IDataTypeComponent *,std::vector<vsc::IModelField *>>;

private:
	IContext								*m_ctxt;
	ComponentMapUP							m_comp_map;

};

} /* namespace arl */

