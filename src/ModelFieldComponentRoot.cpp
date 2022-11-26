/*
 * ModelFieldComponentRoot.cpp
 *
 * Copyright 2022 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author:
 */
#include <algorithm>
#include "arl/IVisitor.h"
#include "arl/impl/IsResourcePool.h"
#include "arl/impl/TaskVisitActionTypeClaimRef.h"
#include "vsc/impl/DebugMacros.h"
#include "vsc/impl/ModelBuildContext.h"
#include "vsc/impl/TaskResolveFieldRefExpr.h"
#include "ModelFieldComponentRoot.h"
#include "TaskCollectPools.h"
#include "TaskVisitComponentFields.h"


namespace arl {
ModelFieldComponentRoot::ModelFieldComponentRoot(
    IContext            *ctxt,
    const std::string   &name,
    IDataTypeComponent  *type) : ModelFieldComponent(name, type) {
    m_init_pass = 0;

    DEBUG_INIT("ModelFieldComponentRoot", ctxt->getDebugMgr());

//    m_comp_map.init(this);
}

ModelFieldComponentRoot::~ModelFieldComponentRoot() {

}

void ModelFieldComponentRoot::initCompTree() {

    m_init_pass = 0;

    // We first build information about component types and instances
    TaskVisitComponentFields(
        [&](IModelFieldComponent *f) { enterComponentScope(dynamic_cast<ModelFieldComponent *>(f)); },
        [&](IModelFieldComponent *f) { leaveComponentScope(); }).visit(this);

    // Now, want to do a bit of organization to ensure collections are ordered
    // in a way that makes constraint construction easy
    for (RefTCompPoolIdM::iterator
        it=m_ref_comp_pool_id_m.begin();
        it!=m_ref_comp_pool_id_m.end(); it++) {
        // Order the mapping according to the component ID
        std::sort(
            it->second.begin(),
            it->second.end(),
            [](const CompIdPoolId &i1, const CompIdPoolId &i2) { return i1.first < i2.first; }
        );
    }
    
    for (ClaimTCompIdPoolM::iterator
        it=m_claim_comp_id_pool_m.begin();
        it!=m_claim_comp_id_pool_m.end(); it++) {
        std::sort(
            it->second.begin(),
            it->second.end(),
            [](const CompIdPoolH &i1, const CompIdPoolH &i2) { return i1.first < i2.first; }
        );
    }

    m_init_pass = 1;
}

const std::vector<IModelFieldComponent *> &ModelFieldComponentRoot::getCompTypeInsts(
        IDataTypeComponent *t) const {
    CompType2InstMapT::const_iterator it = m_comp_type_inst_m.find(t);

    if (it != m_comp_type_inst_m.end()) {
        return it->second.instances;
    } else {
        return m_empty_comp_l;
    }
}

const std::vector<int32_t> &ModelFieldComponentRoot::getCompTypeSubInsts(
        IDataTypeComponent *target_t,
        IDataTypeComponent *parent_t,
        int32_t             parent_id) const {
    // First, find the parent-type info
    CompType2InstMapT::const_iterator it = m_comp_type_inst_m.find(parent_t);

    if (it != m_comp_type_inst_m.end()) {
        CompType2InstIdMapT::const_iterator l_it = it->second.subinst_m.at(parent_id).find(target_t);

        if (l_it != it->second.subinst_m.at(parent_id).end()) {
            return l_it->second;
        } else {
            //
        }
    } else {
        // 
    }
}

const std::vector<IModelFieldPool *> &ModelFieldComponentRoot::getPools(
    vsc::IDataType *t) {
    return m_obj_type_pool_m.find(t)->second;
}

void ModelFieldComponentRoot::accept(vsc::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitModelFieldComponentRoot(this);
    } else if (v->cascade()) {
        v->visitModelField(this);
    }
}

void ModelFieldComponentRoot::enterComponentScope(ModelFieldComponent *comp) {
    CompType2InstMapT::iterator ct_it = m_comp_type_inst_m.find(
        comp->getDataTypeT<IDataTypeComponent>());

    int32_t inst_id = 0;

    if (ct_it == m_comp_type_inst_m.end()) {
        comp->setId(0);
        ct_it = m_comp_type_inst_m.insert({
            comp->getDataTypeT<IDataTypeComponent>(),
            {
                .instances={comp},
                .subinst_m={CompType2InstIdMapT()}
            }
        }).first;
        m_comp_type_l.push_back(comp->getDataTypeT<IDataTypeComponent>());

        // Since we know this is the first entry of its type,
        // we must ensure that it is also considered a sub-instance
        ct_it->second.subinst_m.at(0).insert({
            comp->getDataTypeT<IDataTypeComponent>(),
            {0}
        });
    } else {
        inst_id = ct_it->second.instances.size();
        comp->setId(inst_id);
        ct_it->second.instances.push_back(comp);
        ct_it->second.subinst_m.push_back(CompType2InstIdMapT());
    }

    // Walk back up the stack adding in the notion
    // that this Type/Id pair is accessible
    for (int32_t i=m_inst_data_s.size()-1; i>=0; i--) {
        int32_t id = m_inst_id_s.at(i);
        CompType2InstData *inst_data = m_inst_data_s.at(i);
        CompType2InstIdMapT &t2i_m = inst_data->subinst_m.at(i);

        CompType2InstIdMapT::iterator it = t2i_m.find(
            comp->getDataTypeT<IDataTypeComponent>());
        if (it == t2i_m.end()) {
            t2i_m.insert({
                comp->getDataTypeT<IDataTypeComponent>(),
                {inst_id}
            });
        } else {
            it->second.push_back(inst_id);
        }
    }

    // Add all pools from this level
    TaskCollectPools([&] (IModelFieldPool *pool) { addPool(pool);});

    processBinds(comp);

    m_inst_data_s.push_back(&ct_it->second);
    m_inst_id_s.push_back(inst_id);
}

void ModelFieldComponentRoot::processBinds(ModelFieldComponent *comp) {

    // Process binds at this level
    if (m_type_pool_s.size()) {
        // Start from the previous level's binding info
        m_type_pool_s.push_back(m_type_pool_s.back());
    } else {
        // Start fresh
        m_type_pool_s.push_back(TypePoolMapFrame());
    }

    TypePoolMapFrame &bind_f = m_type_pool_s.back();
    vsc::ModelBuildContext build_ctxt(0);
    build_ctxt.pushTopDownScope(comp);
    vsc::TaskResolveFieldRefExpr resolver(&build_ctxt);

    // Process bind statements and update the bind-info map
	for (std::vector<IPoolBindDirectiveUP>::const_iterator
		it=comp->getDataTypeT<IDataTypeComponent>()->getPoolBindDirectives().begin();
		it!=comp->getDataTypeT<IDataTypeComponent>()->getPoolBindDirectives().end(); it++) {
		switch ((*it)->kind()) {
			case PoolBindKind::All: {
				vsc::IModelField *field = resolver.resolve((*it)->getPool());
				IModelFieldPool *pool = dynamic_cast<IModelFieldPool *>(field);
				TypePoolMapT::const_iterator b_it = bind_f.wildcard_m.find(pool->getDataTypePool());

				DEBUG("BindAll: %s", pool->name().c_str());

				if (b_it == bind_f.wildcard_m.end()) {
					// No current bind, so add one
					DEBUG("  Add to bind map");
					bind_f.wildcard_m.insert({pool->getDataTypePool(), pool});
				} else {
					DEBUG("  Already mapped to pool %s", b_it->second->name().c_str());
				}
				} break;
			case PoolBindKind::Ref: {
				fprintf(stdout, "TODO: handle direct-ref binds\n");
				} break;
		}
	}

    for (std::vector<IDataTypeAction *>::const_iterator
        it=comp->getDataTypeT<IDataTypeComponent>()->getActionTypes().begin();
        it!=comp->getDataTypeT<IDataTypeComponent>()->getActionTypes().end(); it++) {
        TaskVisitActionTypeClaimRef(
            [&](ITypeFieldInOut *f) { processTypeFieldRef(comp, f); },
            [&](ITypeFieldClaim *f) { processTypeFieldClaim(comp, f); }).visit(*it);
    }
}

void ModelFieldComponentRoot::leaveComponentScope() {
    m_type_pool_s.pop_back();
    m_inst_data_s.pop_back();
    m_inst_id_s.pop_back();
}

void ModelFieldComponentRoot::addPool(IModelFieldPool *pool) {
    DEBUG_ENTER("addPool %s", pool->name().c_str());

    if (IsResourcePool().test(pool)) {
        ResTObjectM::iterator it = m_res_obj_m.find(pool->getDataTypePool());

        if (it == m_res_obj_m.end()) {
            it = m_res_obj_m.insert({
                pool->getDataTypePool(),
                {}
            }).first;
        }

        pool->setGlobalPoolRange(
            it->second.size(),
            it->second.size()+pool->getObjects().size()-1);
        for (std::vector<vsc::IModelFieldUP>::const_iterator
            o_it=pool->getObjects().begin();
            o_it!=pool->getObjects().end(); o_it++) {
            it->second.push_back(o_it->get());
        }
    } else {
        ObjType2PoolMapT::iterator it = m_obj_type_pool_m.find(pool->getDataType());

        if (it == m_obj_type_pool_m.end()) {
            it = m_obj_type_pool_m.insert({
                pool->getDataType(),
                {}
            }).first;
        }

        pool->setId(it->second.size());
        it->second.push_back(pool);
    }

    DEBUG_LEAVE("addPool %s", pool->name().c_str());
}

void ModelFieldComponentRoot::processTypeFieldRef(
        ModelFieldComponent         *comp,
        ITypeFieldInOut             *ref) {
    const TypePoolMapFrame &bind_f = m_type_pool_s.back();
    FieldPoolMapT::const_iterator field_it;
    TypePoolMapT::const_iterator type_it;

    if ((field_it=bind_f.field_m.find(ref)) != bind_f.field_m.end()) {
        RefTCompPoolIdM::iterator it = m_ref_comp_pool_id_m.find(ref);

        if (it == m_ref_comp_pool_id_m.end()) {
            m_ref_comp_pool_id_m.insert({ref, {}});
        }
        it->second.push_back({comp->getId(), field_it->second->getId()});
    } else if ((type_it=bind_f.wildcard_m.find(ref->getDataType())) != bind_f.wildcard_m.end()) {
        RefTCompPoolIdM::iterator it = m_ref_comp_pool_id_m.find(ref);

        if (it == m_ref_comp_pool_id_m.end()) {
            m_ref_comp_pool_id_m.insert({ref, {}});
        }
        it->second.push_back({comp->getId(), type_it->second->getId()});

    } else {
        DEBUG("Error: no mapping");
    }
}

void ModelFieldComponentRoot::processTypeFieldClaim(
        ModelFieldComponent         *comp,
        ITypeFieldClaim             *claim) {
    const TypePoolMapFrame &bind_f = m_type_pool_s.back();
    FieldPoolMapT::const_iterator field_it;
    TypePoolMapT::const_iterator type_it;

    if ((field_it=bind_f.field_m.find(claim)) != bind_f.field_m.end()) {
        // Single-claim bind to pool in 'comp' context
        // Add this info to the relevant type map
        ClaimTCompIdPoolM::iterator it = m_claim_comp_id_pool_m.find(claim);

        if (it == m_claim_comp_id_pool_m.end()) {
            it = m_claim_comp_id_pool_m.insert({claim, {}}).first;
        }
        it->second.push_back({comp->getId(), field_it->second});

    } else if ((type_it=bind_f.wildcard_m.find(claim->getDataType())) != bind_f.wildcard_m.end()) {
        ClaimTCompIdPoolM::iterator it = m_claim_comp_id_pool_m.find(claim);

        if (it == m_claim_comp_id_pool_m.end()) {
            it = m_claim_comp_id_pool_m.insert({claim, {}}).first;
        }
        it->second.push_back({comp->getId(), type_it->second});
    } else {
        DEBUG("Error: no mapping");
    }
}

vsc::IDebug *ModelFieldComponentRoot::m_dbg = 0;

}
