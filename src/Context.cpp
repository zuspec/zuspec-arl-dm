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

namespace arl {

Context::Context(vsc::IContext *ctxt) : m_ctxt(ctxt) {

}

Context::~Context() {
	if (m_ctxt) {
		delete m_ctxt;
	}
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

IDataTypeAction *Context::findDataTypeAction(const std::string &name) {
	std::unordered_map<std::string,IDataTypeActionUP>::const_iterator it;

	if ((it=m_action_type_m.find(name)) != m_action_type_m.end()) {
		return it->second.get();
	} else {
		return 0;
	}
}

IDataTypeAction *Context::mkDataTypeAction(const std::string &name) {
	return new DataTypeAction(name);
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

vsc::IModelFieldRoot *Context::buildModelField(
		vsc::IDataTypeStruct			*dt,
		const std::string		&name) {
	return m_ctxt->buildModelField(dt, name);
}

vsc::ICompoundSolver *Context::mkCompoundSolver() {
	return m_ctxt->mkCompoundSolver();
}

vsc::IDataTypeInt *Context::findDataTypeInt(
		bool			is_signed,
		int32_t			width) {
	return m_ctxt->findDataTypeInt(is_signed, width);
}

/**
 * Returns a new datatype. The expectation is that
 * it will be subsequently added to the context
 */
vsc::IDataTypeInt *Context::mkDataTypeInt(
		bool			is_signed,
		int32_t			width) {
	return m_ctxt->mkDataTypeInt(is_signed, width);
}

bool Context::addDataTypeInt(vsc::IDataTypeInt *t) {
	return m_ctxt->addDataTypeInt(t);
}

vsc::IDataTypeStruct *Context::findDataTypeStruct(const std::string &name) {
	return m_ctxt->findDataTypeStruct(name);
}

vsc::IDataTypeStruct *Context::mkDataTypeStruct(const std::string &name) {
	return m_ctxt->mkDataTypeStruct(name);
}

bool Context::addDataTypeStruct(vsc::IDataTypeStruct *t) {
	return m_ctxt->addDataTypeStruct(t);
}

vsc::IModelConstraintBlock *Context::mkModelConstraintBlock(
		const std::string &name) {
	return m_ctxt->mkModelConstraintBlock(name);
}

vsc::IModelConstraintExpr *Context::mkModelConstraintExpr(
		vsc::IModelExpr		*expr) {
	return m_ctxt->mkModelConstraintExpr(expr);
}

vsc::IModelExprBin *Context::mkModelExprBin(
		vsc::IModelExpr		*lhs,
		vsc::BinOp			op,
		vsc::IModelExpr		*rhs) {
	return m_ctxt->mkModelExprBin(lhs, op, rhs);
}

vsc::IModelExprFieldRef *Context::mkModelExprFieldRef(
		vsc::IModelField		*field) {
	return m_ctxt->mkModelExprFieldRef(field);
}

vsc::IModelExprVal *Context::mkModelExprVal(vsc::IModelVal *v) {
	return m_ctxt->mkModelExprVal(v);
}

vsc::IModelFieldRoot *Context::mkModelFieldRoot(
		vsc::IDataType 			*type,
		const std::string	&name) {
	return m_ctxt->mkModelFieldRoot(type, name);
}

vsc::IModelFieldType *Context::mkModelFieldType(
		vsc::ITypeField			*type) {
	return m_ctxt->mkModelFieldType(type);
}

vsc::IModelVal *Context::mkModelVal() {
	return m_ctxt->mkModelVal();
}

vsc::IRandomizer *Context::mkRandomizer(
		vsc::ISolverFactory		*solver_factory,
		vsc::IRandState			*randstate) {
	return m_ctxt->mkRandomizer(solver_factory, randstate);
}


vsc::IRandState *Context::mkRandState(uint32_t seed) {
	return m_ctxt->mkRandState(seed);
}

vsc::ITask *Context::mkTask(vsc::TaskE id) {
	return m_ctxt->mkTask(id);
}

vsc::ITypeExprBin *Context::mkTypeExprBin(
		vsc::ITypeExpr		*lhs,
		vsc::BinOp			op,
		vsc::ITypeExpr		*rhs) {
	return m_ctxt->mkTypeExprBin(lhs, op, rhs);
}

vsc::ITypeConstraintBlock *Context::mkTypeConstraintBlock(const std::string &name) {
	return m_ctxt->mkTypeConstraintBlock(name);
}

vsc::ITypeConstraintExpr *Context::mkTypeConstraintExpr(vsc::ITypeExpr *e) {
	return m_ctxt->mkTypeConstraintExpr(e);
}

vsc::ITypeConstraintScope *Context::mkTypeConstraintScope() {
	return m_ctxt->mkTypeConstraintScope();
}

vsc::ITypeExprFieldRef *Context::mkTypeExprFieldRef() {
	return m_ctxt->mkTypeExprFieldRef();
}

vsc::ITypeExprVal *Context::mkTypeExprVal(const vsc::IModelVal *v) {
	return m_ctxt->mkTypeExprVal(v);
}

vsc::ITypeField *Context::mkTypeField(
		const std::string		&name,
		vsc::IDataType				*dtype,
		vsc::TypeFieldAttr			attr,
		vsc::IModelVal				*init) {
	return m_ctxt->mkTypeField(name, dtype, attr, init);
}


} /* namespace arl */
