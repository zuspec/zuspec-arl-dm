/*
 * ComponentMap.cpp
 *
 *  Created on: May 15, 2022
 *      Author: mballance
 */

#include "DebugMacros.h"
#include "ComponentMap.h"
#include "zsp/arl/dm/IDataTypeComponent.h"
#include "zsp/arl/dm/IModelFieldComponent.h"

namespace zsp {
namespace arl {
namespace dm {


ComponentMap::ComponentMap() {
	DEBUG_INIT("ComponentMap");
}

ComponentMap::~ComponentMap() {
	// TODO Auto-generated destructor stub
}

void ComponentMap::init(IModelFieldComponent *comp) {
	IDataTypeComponent *comp_t = comp->getDataTypeT<IDataTypeComponent>();
	std::vector<IModelFieldComponent *> comp_l;
	comp_l.push_back(comp);
	m_comp_type_inst_m.insert({comp_t, comp_l});
	m_comp_types.push_back(comp_t);
}

void ComponentMap::addSubComponentMap(const IComponentMap *m) {
	DEBUG_ENTER("addSubComponentMap");
	for (std::vector<IDataTypeComponent *>::const_iterator
		it=m->getComponentTypes().begin();
		it!=m->getComponentTypes().end(); it++) {
		CompType2InstMapT::iterator m_it = m_comp_type_inst_m.find(*it);
		if (m_it == m_comp_type_inst_m.end()) {
			m_it = m_comp_type_inst_m.insert({*it, {}}).first;
			m_comp_types.push_back(*it);
		}
		for (std::vector<IModelFieldComponent *>::const_iterator
			c_it=m->getSubContexts(*it).begin();
			c_it!=m->getSubContexts(*it).end(); c_it++) {
			m_it->second.push_back(*c_it);
		}
	}
	DEBUG_LEAVE("addSubComponentMap");
}

const std::vector<IModelFieldComponent *> &ComponentMap::getSubContexts(IDataTypeComponent *t) const {
	CompType2InstMapT::const_iterator it = m_comp_type_inst_m.find(t);
	if (it != m_comp_type_inst_m.end()) {
		return it->second;
	} else {
		return m_empty;
	}
}

void ComponentMap::addPoolMapping(vsc::dm::ITypeField *claim_ref, IModelFieldPool *pool) {
	m_claim_ref_pool_m.insert({claim_ref, pool});
}

IModelFieldPool *ComponentMap::getPool(vsc::dm::ITypeField *claim_ref) const {
	ClaimRef2PoolMapT::const_iterator it = m_claim_ref_pool_m.find(claim_ref);

	if (it == m_claim_ref_pool_m.end()) {
		return 0;
	} else {
		return it->second;
	}
}

}
}
}
