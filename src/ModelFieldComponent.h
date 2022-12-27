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
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IDataTypeComponent.h"
#include "zsp/arl/dm/IModelFieldComponent.h"
#include "vsc/dm/IModelField.h"
#include "vsc/dm/IModelVal.h"
#include "ComponentMap.h"
#include "ModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class ModelFieldComponentRoot;

class ModelFieldComponent : 
	public virtual IModelFieldComponent,
	public virtual ModelField {
public:
	ModelFieldComponent(
		const std::string			&name,
		IDataTypeComponent			*type);

	ModelFieldComponent(
		vsc::dm::ITypeField				*type);

	virtual ~ModelFieldComponent();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual vsc::dm::IDataType *getDataType() const override {
        return m_dt;
    }

	virtual int32_t getId() const { return m_id; }

	void setId(int32_t id) { m_id = id; }

	virtual void accept(vsc::dm::IVisitor *v) override;

protected:

	ModelFieldComponentRoot *getRoot();

private:
	using CompTCompIdM=std::unordered_map<IDataTypeComponent *, std::vector<int32_t>>;
	using CompTCompInstM=std::unordered_map<IDataTypeComponent *,std::vector<vsc::dm::IModelField *>>;
	using RefTPoolIdM=std::unordered_map<ITypeFieldInOut *,int32_t>;


protected:
	IContext								*m_ctxt;
	int32_t									m_id;
	std::string								m_name;
	vsc::dm::IDataType							*m_dt;
	vsc::dm::ITypeField							*m_type;


	// Map from the field-type handle of an action declared in
	// this component type to the global pool-id that it is
	// associated with.
	RefTPoolIdM								m_ref_pool_id_m;

//	ComponentMap							m_comp_map;

};

}
}
}

