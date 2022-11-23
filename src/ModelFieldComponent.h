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

class ModelFieldComponent : public virtual IModelFieldComponent {
public:
	ModelFieldComponent(arl::IContext *ctxt);

	virtual ~ModelFieldComponent();

	virtual void initCompTree() override;

	virtual IComponentMap *getCompMap() override { return &m_comp_map; }

	virtual void accept(vsc::IVisitor *v) override;

private:
	using CompTCompIdM=std::unordered_map<IDataTypeComponent *, std::vector<int32_t>>;
	using CompTCompInstM=std::unordered_map<IDataTypeComponent *,std::vector<vsc::IModelField *>>;
	using RefTPoolIdM=std::unordered_map<ITypeFieldInOut *,int32_t>;


protected:
	IContext								*m_ctxt;
	int32_t									m_id;

	// Map from the field-type handle of an action declared in
	// this component type to the global pool-id that it is
	// associated with.
	RefTPoolIdM								m_ref_pool_id_m;

	ComponentMap							m_comp_map;

};

} /* namespace arl */

