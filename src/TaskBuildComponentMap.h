/*
 * TaskBuildComponentMap.h
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#pragma once
#include <unordered_map>
#include "arl/IModelFieldComponent.h"
#include "arl/impl/VisitorBase.h"
#include "vsc/IModelField.h"
#include "ComponentMap.h"

namespace arl {

class TaskBuildComponentMap : public virtual VisitorBase {
public:
	TaskBuildComponentMap();

	virtual ~TaskBuildComponentMap();

	void build(IModelFieldComponent *root);

	virtual void visitModelFieldComponent(IModelFieldComponent *f) override;

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) override;

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) override;

private:
	using TypePoolMapT=std::unordered_map<vsc::IDataType *, IModelFieldPool *>;
	using FieldPoolMapT=std::unordered_map<vsc::ITypeField *, IModelFieldPool *>;

	struct TypePoolMapFrame {
		TypePoolMapT						m_wildcard_m;
		FieldPoolMapT						m_field_m;
	};

private:
	IModelFieldComponent										*m_comp;
	std::vector<std::vector<IModelFieldComponent *>>			m_component_s;
	std::vector<TypePoolMapFrame>								m_type_pool_map_s;

};

} /* namespace arl */

