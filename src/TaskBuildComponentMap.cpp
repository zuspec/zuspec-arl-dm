/*
 * TaskBuildComponentMap.cpp
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#include "vsc/impl/ModelBuildContext.h"
#include "vsc/impl/TaskResolveFieldRefExpr.h"
#include "DebugMacros.h"
#include "DataTypeComponent.h"
#include "TaskBuildComponentMap.h"
#include "TaskIsDataTypeComponent.h"

namespace arl {

TaskBuildComponentMap::TaskBuildComponentMap() : m_comp(0) {
	DEBUG_INIT("TaskBuildComponentMap");
	// TODO Auto-generated constructor stub

}

TaskBuildComponentMap::~TaskBuildComponentMap() {
	// TODO Auto-generated destructor stub
}

void TaskBuildComponentMap::build(IModelFieldComponent *root) {
	DEBUG_ENTER("build");
	m_component_s.push_back({});
	root->accept(m_this);
	m_component_s.pop_back();
	DEBUG_LEAVE("build");
}

void TaskBuildComponentMap::visitModelFieldComponent(IModelFieldComponent *f) {
	DEBUG_ENTER("visitModelFieldComponent %s %s",
		f->name().c_str(),
		f->getDataTypeT<IDataTypeComponent>()->name().c_str());

	// TODO:

	// Process binds at this level
	if (m_type_pool_map_s.size()) {
		m_type_pool_map_s.push_back(m_type_pool_map_s.back());
	} else {
		m_type_pool_map_s.push_back(TypePoolMapFrame());
	}

	TypePoolMapFrame &bind_f = m_type_pool_map_s.back();
	vsc::ModelBuildContext build_ctxt(0);
	build_ctxt.pushTopDownScope(f);
	vsc::TaskResolveFieldRefExpr resolver(&build_ctxt);

	for (std::vector<IPoolBindDirectiveUP>::const_iterator
		it=f->getDataTypeT<IDataTypeComponent>()->getPoolBindDirectives().begin();
		it!=f->getDataTypeT<IDataTypeComponent>()->getPoolBindDirectives().end(); it++) {
		switch ((*it)->kind()) {
			case PoolBindKind::All: {
				vsc::IModelField *field = resolver.resolve((*it)->getPool());
				IModelFieldPool *pool = dynamic_cast<IModelFieldPool *>(field);
				TypePoolMapT::const_iterator b_it = bind_f.m_wildcard_m.find(pool->getDataTypePool());

				DEBUG("BindAll: %s", pool->name().c_str());

				if (b_it == bind_f.m_wildcard_m.end()) {
					// No current bind, so add one
					DEBUG("  Add to bind map");
					bind_f.m_wildcard_m.insert({pool->getDataTypePool(), pool});
				} else {
					DEBUG("  Already mapped to pool %s", b_it->second->name().c_str());
				}
				} break;
			case PoolBindKind::Ref: {
				fprintf(stdout, "TODO: handle direct-ref binds\n");
				} break;
		}
	}

	m_comp = f;
	for (std::vector<IDataTypeAction *>::const_iterator
		it=f->getDataTypeT<DataTypeComponent>()->getActionTypes().begin();
		it!=f->getDataTypeT<DataTypeComponent>()->getActionTypes().end(); it++) {
		DEBUG("ActionType %s", (*it)->name().c_str());
		// Process action claims and references
		for (std::vector<vsc::ITypeFieldUP>::const_iterator
			f_it=(*it)->getFields().begin();
			f_it!=(*it)->getFields().end(); f_it++) {
			DEBUG("Visiting field %s", (*f_it)->name().c_str());
			(*f_it)->accept(m_this);
		}
	}
	m_comp = 0;

	// TODO: process component-type fields inside this component
	m_component_s.push_back(std::vector<IModelFieldComponent *>());
	VisitorBase::visitModelFieldComponent(f);

#ifdef UNDEFINED
	// Incorporate map information from sub-components
	for (std::vector<IModelFieldComponent *>::const_iterator
		it=m_component_s.back().begin();
		it!=m_component_s.back().end(); it++) {
		f->getCompMap()->addSubComponentMap((*it)->getCompMap());
	}
#endif

	m_component_s.pop_back();
	m_type_pool_map_s.pop_back();

	// Need to incorporate map data from all sub-component fields
	// into this one

	m_component_s.back().push_back(f);
	DEBUG_LEAVE("visitModelFieldComponent %s %s",
		f->name().c_str(),
		f->getDataTypeT<IDataTypeComponent>()->name().c_str());
}

void TaskBuildComponentMap::visitTypeFieldClaim(ITypeFieldClaim *f) {
	DEBUG_ENTER("visitTypeFieldClaim %s", f->name().c_str());
	const TypePoolMapFrame &bind_f = m_type_pool_map_s.back();
	FieldPoolMapT::const_iterator field_it;
	TypePoolMapT::const_iterator type_it;


#ifdef UNDEFINED
	// First, check direct binds
	if ((field_it=bind_f.m_field_m.find(f)) != bind_f.m_field_m.end()) {
		DEBUG("Have a field-specific mapping");
		m_comp->getCompMap()->addPoolMapping(f, field_it->second);
	} else if ((type_it=bind_f.m_wildcard_m.find(f->getDataType())) != bind_f.m_wildcard_m.end()) {
		DEBUG("Have a wildcard mapping");
		m_comp->getCompMap()->addPoolMapping(f, type_it->second);
	} else {
		DEBUG("ERROR: no mapping");
	}
#endif

	DEBUG_LEAVE("visitTypeFieldClaim %s", f->name().c_str());
}

void TaskBuildComponentMap::visitTypeFieldInOut(ITypeFieldInOut *f) {
	DEBUG_ENTER("visitTypeFieldInOut %s", f->name().c_str());
	const TypePoolMapFrame &bind_f = m_type_pool_map_s.back();
	FieldPoolMapT::const_iterator field_it;
	TypePoolMapT::const_iterator type_it;

#ifdef UNDEFINED
	// First, check direct binds
	if ((field_it=bind_f.m_field_m.find(f)) != bind_f.m_field_m.end()) {
		DEBUG("Have a field-specific mapping");
		m_comp->getCompMap()->addPoolMapping(f, field_it->second);
	} else if ((type_it=bind_f.m_wildcard_m.find(f->getDataType())) != bind_f.m_wildcard_m.end()) {
		DEBUG("Have a wildcard mapping");
		m_comp->getCompMap()->addPoolMapping(f, type_it->second);
	} else {
		DEBUG("ERROR: no mapping");
	}
#endif

	DEBUG_LEAVE("visitTypeFieldInOut %s", f->name().c_str());
}

} /* namespace arl */
