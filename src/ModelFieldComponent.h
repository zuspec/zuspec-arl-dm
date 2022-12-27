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
		vsc::ITypeField				*type);

	virtual ~ModelFieldComponent();

    virtual const std::string &name() const override {
        return m_name;
    }

    virtual vsc::IDataType *getDataType() const override {
        return m_dt;
    }

	virtual int32_t getId() const { return m_id; }

	void setId(int32_t id) { m_id = id; }

	virtual void accept(vsc::IVisitor *v) override;

protected:

	ModelFieldComponentRoot *getRoot();

private:
	using CompTCompIdM=std::unordered_map<IDataTypeComponent *, std::vector<int32_t>>;
	using CompTCompInstM=std::unordered_map<IDataTypeComponent *,std::vector<vsc::IModelField *>>;
	using RefTPoolIdM=std::unordered_map<ITypeFieldInOut *,int32_t>;


protected:
	IContext								*m_ctxt;
	int32_t									m_id;
	std::string								m_name;
	vsc::IDataType							*m_dt;
	vsc::ITypeField							*m_type;


	// Map from the field-type handle of an action declared in
	// this component type to the global pool-id that it is
	// associated with.
	RefTPoolIdM								m_ref_pool_id_m;

//	ComponentMap							m_comp_map;

};

}
}
}

