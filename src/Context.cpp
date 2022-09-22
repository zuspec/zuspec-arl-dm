/*
 * Context.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "Context.h"
#include "DataTypeAction.h"
#include "DataTypeActivityParallel.h"
#include "DataTypeActivitySchedule.h"
#include "DataTypeActivitySequence.h"
#include "DataTypeActivityTraverse.h"
#include "DataTypeComponent.h"
#include "DataTypeFlowObj.h"
#include "DataTypeResource.h"
#include "ModelActivityParallel.h"
#include "ModelActivitySchedule.h"
#include "ModelActivitySequence.h"
#include "ModelActivityTraverse.h"
#include "ModelBuildContext.h"
#include "ModelEvaluator.h"
#include "ModelFieldActionRoot.h"
#include "ModelFieldActionType.h"
#include "ModelFieldComponentRoot.h"
#include "ModelFieldComponentType.h"
#include "ModelFieldPool.h"
#include "PoolBindDirective.h"
#include "TaskBuildModelAction.h"
#include "TaskBuildModelComponent.h"
#include "TaskBuildModelField.h"
#include "TypeFieldActivity.h"
#include "TypeFieldClaim.h"
#include "TypeFieldInOut.h"
#include "TypeFieldPool.h"

namespace arl {

Context::Context(vsc::IContext *ctxt) : vsc::ContextDelegator(ctxt) {

}

Context::~Context() {

}

IModelFieldAction *Context::buildModelAction(
		IDataTypeAction 	*t,
		const std::string	&name) {
	ModelBuildContext ctxt(this);
	return TaskBuildModelAction(&ctxt).build(t, name);
}

IModelFieldComponent *Context::buildModelComponent(
		IDataTypeComponent 	*t,
		const std::string	&name) {
	ModelBuildContext ctxt(this);
	return TaskBuildModelComponent(&ctxt).build(t, name);
}

IDataTypeAction *Context::findDataTypeAction(const std::string &name) {
	std::unordered_map<std::string,IDataTypeActionUP>::const_iterator it;

	if ((it=m_action_type_m.find(name)) != m_action_type_m.end()) {
		return it->second.get();
	} else {
		return 0;
	}
}

IDataTypeAction *Context::mkDataTypeAction(const std::string &name) {
	return new DataTypeAction(this, name);
}

bool Context::addDataTypeAction(IDataTypeAction *t) {
	return m_action_type_m.insert({t->name(), IDataTypeActionUP(t)}).second;
}

IDataTypeActivityParallel *Context::mkDataTypeActivityParallel() {
	return new DataTypeActivityParallel();
}

IDataTypeActivitySchedule *Context::mkDataTypeActivitySchedule() {
	return new DataTypeActivitySchedule();
}

IDataTypeActivitySequence *Context::mkDataTypeActivitySequence() {
	return new DataTypeActivitySequence();
}

IDataTypeActivityTraverse *Context::mkDataTypeActivityTraverse(
		vsc::ITypeExprFieldRef	*target,
		vsc::ITypeConstraint	*with_c) {
	return new DataTypeActivityTraverse(target, with_c);
}

IDataTypeComponent *Context::findDataTypeComponent(const std::string &name) {
	std::unordered_map<std::string,IDataTypeComponentUP>::const_iterator it;

	if ((it=m_component_type_m.find(name)) != m_component_type_m.end()) {
		return it->second.get();
	} else {
		return 0;
	}
}

IDataTypeComponent *Context::mkDataTypeComponent(const std::string &name) {
	return new DataTypeComponent(name);
}

bool Context::addDataTypeComponent(IDataTypeComponent *t) {
	std::unordered_map<std::string,IDataTypeComponentUP>::const_iterator it;

	if ((it=m_component_type_m.find(t->name())) != m_component_type_m.end()) {
		m_component_type_m.insert({t->name(), IDataTypeComponentUP(t)});
		return true;
	} else {
		return false;
	}
}

IDataTypeFlowObj *Context::findDataTypeFlowObj(
		const std::string 	&name,
		FlowObjKindE		kind) {
	std::unordered_map<FlowObjKindE,FlowObjMapT>::const_iterator it;

	if ((it=m_flowobj_kind_m.find(kind)) != m_flowobj_kind_m.end()) {
		FlowObjMapT::const_iterator t_it = it->second.find(name);
		if (t_it != it->second.end()) {
			return t_it->second.get();
		} 
	}
	return 0;
}

IDataTypeFlowObj *Context::mkDataTypeFlowObj(
		const std::string 	&name,
		FlowObjKindE		kind) {
	IDataTypeFlowObj *ret = 0;

	switch (kind) {
		case FlowObjKindE::Resource: {
			ret = new DataTypeResource(this, name);
		} break;
		default:
			ret = new DataTypeFlowObj(name, kind);
	}

	return ret;
}

bool Context::addDataTypeFlowObj(IDataTypeFlowObj *t) {
	std::unordered_map<FlowObjKindE,FlowObjMapT>::iterator it;

	if ((it=m_flowobj_kind_m.find(t->kind())) == m_flowobj_kind_m.end()) {
		it = m_flowobj_kind_m.insert({t->kind(), FlowObjMapT()}).first;
	}

	return it->second.insert({t->name(), IDataTypeFlowObjUP(t)}).second;
}

IModelActivityParallel *Context::mkModelActivityParallel() {
	return new ModelActivityParallel();
}

IModelActivitySchedule *Context::mkModelActivitySchedule() {
	return new ModelActivitySchedule("", 0);
}

IModelActivitySequence *Context::mkModelActivitySequence() {
	return new ModelActivitySequence("", 0);
}

IModelActivityTraverse *Context::mkModelActivityTraverse(
		IModelFieldAction			*target,
		vsc::IModelConstraint		*with_c) {
	return new ModelActivityTraverse(target, with_c);
}

IModelEvaluator *Context::mkModelEvaluator() {
	return new ModelEvaluator(this);
}

IModelFieldAction *Context::mkModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type) {
	return new ModelFieldActionRoot(name, type);
}

IModelFieldAction *Context::mkModelFieldActionType(
			vsc::ITypeField			*type) {
	return new ModelFieldActionType(type);
}

IModelFieldComponent *Context::mkModelFieldComponentRoot(
			IDataTypeComponent		*type,
			const std::string		&name) {
	return new ModelFieldComponentRoot(this, name, type);
}

IModelFieldComponent *Context::mkModelFieldComponentType(
			vsc::ITypeField         *type) {
	return new ModelFieldComponentType(this, type);
}

IModelFieldPool *Context::mkModelFieldPoolType(
			vsc::ITypeField			*type) {
	return new ModelFieldPool(type->name(), type->getDataType());
}

IPoolBindDirective *Context::mkPoolBindDirective(
			PoolBindKind			kind,
			vsc::ITypeExprFieldRef	*pool,
			vsc::ITypeExprFieldRef	*target) {
	return new PoolBindDirective(kind, pool, target);
}

ITypeFieldActivity *Context::mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) {
	return new TypeFieldActivity(name, type, owned);
}

ITypeFieldClaim *Context::mkTypeFieldClaim(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_lock) {
	return new TypeFieldClaim(name, type, is_lock);
}

ITypeFieldInOut *Context::mkTypeFieldInOut(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_input) {
	return new TypeFieldInOut(name, type, is_input);
}

ITypeFieldPool *Context::mkTypeFieldPool(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					own,
			vsc::TypeFieldAttr		attr,
			int32_t					decl_size) {
	return new TypeFieldPool(this, name, type, own, attr, decl_size);
}

} /* namespace arl */
