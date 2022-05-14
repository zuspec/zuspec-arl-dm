/*
 * Context.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "Context.h"
#include "DataTypeAction.h"
#include "DataTypeComponent.h"
#include "ModelEvaluator.h"
#include "TaskBuildModelAction.h"
#include "TaskBuildModelComponent.h"
#include "TaskBuildModelField.h"
#include "TypeActivityStmtTraverseType.h"
#include "TypeFieldClaim.h"
#include "TypeFieldInOut.h"
#include "TypeFieldPool.h"

namespace arl {

Context::Context(vsc::IContext *ctxt) : vsc::ContextDelegator(ctxt) {

}

Context::~Context() {

}

vsc::IModelField *Context::buildModelAction(
		IDataTypeAction 	*t,
		const std::string	&name) {
	return TaskBuildModelAction(this).build(t, name);
}

vsc::IModelField *Context::buildModelComponent(
		IDataTypeComponent 	*t,
		const std::string	&name) {
	return TaskBuildModelComponent(this).build(t, name);
}

vsc::IModelField *Context::buildModelField(
			vsc::IDataTypeStruct	*dt,
			const std::string		&name) {
	return TaskBuildModelField(this).build(dt, name);
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

IDataTypeFlowObj *Context::findDataTypeFlowObj(const std::string &name) {
	std::unordered_map<std::string,IDataTypeFlowObjUP>::const_iterator it;

	if ((it=m_flowobj_type_m.find(name)) != m_flowobj_type_m.end()) {
		return it->second.get();
	} else {
		return 0;
	}
}

IDataTypeFlowObj *Context::mkDataTypeFlowObj(
		const std::string 	&name,
		FlowObjKindE		kind) {

}

bool Context::addDataTypeFlowObj(IDataTypeFlowObj *t) {

}

IModelEvaluator *Context::mkModelEvaluator() {
	return new ModelEvaluator(this);
}

ITypeActivityStmtTraverseType *Context::mkTypeActivityStmtTraverseType(
			IDataTypeAction			*action_t,
			vsc::ITypeConstraint	*constraint) {
	return new TypeActivityStmtTraverseType(action_t, constraint);
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
			vsc::TypeFieldAttr		attr,
			int32_t					decl_size) {
	return new TypeFieldPool(name, type, attr, decl_size);
}

} /* namespace arl */
