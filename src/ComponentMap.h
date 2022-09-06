/*
 * ComponentMap.h
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "arl/IComponentMap.h"
#include "arl/IModelFieldComponent.h"
#include "vsc/IModelField.h"

namespace arl {

class IDataTypeComponent;

class ComponentMap;
using ComponentMapUP=std::unique_ptr<ComponentMap>;

/**
 * @brief Manages resource information for a component instance
 * - Given a component type, what instances exist below?
 * - Given an action claim or ref handle, what pool is it mapped to?
 */
class ComponentMap : public virtual IComponentMap {
public:
	ComponentMap();

	virtual ~ComponentMap();

	void init(IModelFieldComponent *comp);

    virtual void addSubComponentMap(const IComponentMap *m) override;

    virtual const std::vector<IModelFieldComponent *> &getSubContexts(IDataTypeComponent *t) const override;

    virtual const std::vector<IDataTypeComponent *> &getComponentTypes() const override {
		return m_comp_types;
	}

    virtual void addPoolMapping(vsc::ITypeField *claim_ref, IModelFieldPool *pool) override;

    virtual IModelFieldPool *getPool(vsc::ITypeField *claim_ref) const override;

private:
	using CompType2InstMapT=std::unordered_map<IDataTypeComponent *, std::vector<IModelFieldComponent *>>;
	using ClaimRef2PoolMapT=std::unordered_map<vsc::ITypeField *, IModelFieldPool *>;

private:
	std::vector<IModelFieldComponent *>		m_empty;
	CompType2InstMapT						m_comp_type_inst_m;
	std::vector<IDataTypeComponent *>		m_comp_types;
	ClaimRef2PoolMapT						m_claim_ref_pool_m;
};

} /* namespace arl */

