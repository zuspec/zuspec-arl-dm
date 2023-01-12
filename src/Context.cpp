/*
 * Context.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "Context.h"
#include "DataTypeAction.h"
#include "DataTypeActivityParallel.h"
#include "DataTypeActivityReplicate.h"
#include "DataTypeActivitySchedule.h"
#include "DataTypeActivitySequence.h"
#include "DataTypeActivityTraverse.h"
#include "DataTypeComponent.h"
#include "DataTypeFlowObj.h"
#include "DataTypeFunction.h"
#include "DataTypeFunctionImport.h"
#include "DataTypeFunctionParamDecl.h"
#include "DataTypeResource.h"
#include "ModelActivityIterator.h"
#include "ModelActivityParallel.h"
#include "ModelActivityReplicate.h"
#include "ModelActivitySchedule.h"
#include "ModelActivityScope.h"
#include "ModelActivitySequence.h"
#include "ModelActivityTraverse.h"
#include "zsp/arl/dm/impl/ModelBuildContext.h"
#include "ModelFieldActionRoot.h"
#include "ModelFieldActionType.h"
#include "ModelFieldClaim.h"
#include "ModelFieldComponentRoot.h"
#include "ModelFieldComponentType.h"
#include "ModelFieldExecutor.h"
#include "ModelFieldExecutorClaim.h"
#include "ModelFieldInOut.h"
#include "ModelFieldPool.h"
#include "PoolBindDirective.h"
#include "TaskBuildModelAction.h"
#include "TaskBuildModelComponent.h"
#include "TaskBuildModelField.h"
#include "TypeExprMethodCallContext.h"
#include "TypeExprMethodCallStatic.h"
#include "TypeExecProc.h"
#include "TypeFieldActivity.h"
#include "TypeFieldClaim.h"
#include "TypeFieldExecutor.h"
#include "TypeFieldExecutorClaim.h"
#include "TypeFieldInOut.h"
#include "TypeFieldPool.h"
#include "TypeProcStmtAssign.h"
#include "TypeProcStmtBreak.h"
#include "TypeProcStmtContinue.h"
#include "TypeProcStmtExpr.h"
#include "TypeProcStmtForeach.h"
#include "TypeProcStmtIfElse.h"
#include "TypeProcStmtMatch.h"
#include "TypeProcStmtRepeat.h"
#include "TypeProcStmtRepeatWhile.h"
#include "TypeProcStmtReturn.h"
#include "TypeProcStmtScope.h"
#include "TypeProcStmtVarDecl.h"
#include "TypeProcStmtWhile.h"

namespace zsp {
namespace arl {
namespace dm {


Context::Context(vsc::dm::IContext *ctxt) : vsc::dm::ContextDelegator(ctxt) {

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

IDataTypeFunction *Context::findDataTypeFunction(const std::string &name) {
	std::unordered_map<std::string,IDataTypeFunctionUP>::const_iterator it;

	if ((it=m_function_type_m.find(name)) != m_function_type_m.end()) {
		return it->second.get();
	} else {
		return 0;
	}
}

IDataTypeFunction *Context::mkDataTypeFunction(
		const std::string		&name,
		vsc::dm::IDataType			*rtype,
		bool					own) {
	return new DataTypeFunction(this, name, rtype, own);
}

bool Context::addDataTypeFunction(IDataTypeFunction *f) {
	if (m_function_type_m.find(f->name()) != m_function_type_m.end()) {
		m_function_type_m.insert({f->name(), IDataTypeFunctionUP(f)});
		return true;
	} else {
		return false;
	}
}

IDataTypeFunctionImport *Context::mkDataTypeFunctionImport(
            const std::string       &lang) {
    return new DataTypeFunctionImport(lang);
}

IDataTypeFunctionParamDecl *Context::mkDataTypeFunctionParamDecl(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					own,
			vsc::dm::ITypeExpr			*init) {
	return new DataTypeFunctionParamDecl(name, type, own, init);
}

IDataTypeActivityParallel *Context::mkDataTypeActivityParallel() {
	return new DataTypeActivityParallel();
}

IDataTypeActivityReplicate *Context::mkDataTypeActivityReplicate(
			vsc::dm::ITypeExpr			*count) {
	return new DataTypeActivityReplicate(this, count);
}

IDataTypeActivitySchedule *Context::mkDataTypeActivitySchedule() {
	return new DataTypeActivitySchedule();
}

IDataTypeActivitySequence *Context::mkDataTypeActivitySequence() {
	return new DataTypeActivitySequence();
}

IDataTypeActivityTraverse *Context::mkDataTypeActivityTraverse(
		vsc::dm::ITypeExprFieldRef	*target,
		vsc::dm::ITypeConstraint	*with_c) {
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
	return new DataTypeComponent(this, name);
}

bool Context::addDataTypeComponent(IDataTypeComponent *t) {
	std::unordered_map<std::string,IDataTypeComponentUP>::const_iterator it;

	if ((it=m_component_type_m.find(t->name())) == m_component_type_m.end()) {
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
			ret = new DataTypeFlowObj(this, name, kind);
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

IModelActivityReplicate *Context::mkModelActivityReplicate(
			vsc::dm::IModelExpr			*count) {
	return new ModelActivityReplicate(this, count);
}

IModelActivitySchedule *Context::mkModelActivitySchedule() {
	return new ModelActivitySchedule("", 0);
}

IModelActivityScope *Context::mkModelActivityScope(ModelActivityScopeT t) {
	return new ModelActivityScope(t);
}

IModelActivitySequence *Context::mkModelActivitySequence() {
	return new ModelActivitySequence("", 0);
}

IModelActivityTraverse *Context::mkModelActivityTraverse(
		IModelFieldAction			*target,
		vsc::dm::IModelConstraint		*with_c,
		bool						own_with_c,
		IModelActivity				*activity,
		bool						owned) {
	return new ModelActivityTraverse(
		target, 
		with_c,
		own_with_c,
		activity,
		owned);
}

IModelEvalIterator *Context::mkModelEvalIterator(IModelActivityScope *activity) {
    return new ModelActivityIterator(activity);
}

IModelFieldAction *Context::mkModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type) {
	return new ModelFieldActionRoot(name, type);
}

IModelFieldAction *Context::mkModelFieldActionType(
			vsc::dm::ITypeField			*type) {
	return new ModelFieldActionType(type);
}

IModelFieldClaim *Context::mkModelFieldClaim(
			ITypeFieldClaim			*type) {
	return new ModelFieldClaim(type);
}

IModelFieldComponent *Context::mkModelFieldComponentRoot(
			IDataTypeComponent		*type,
			const std::string		&name) {
	return new ModelFieldComponentRoot(this, name, type);
}

IModelFieldComponent *Context::mkModelFieldComponentType(
			vsc::dm::ITypeField         *type) {
	return new ModelFieldComponentType(type);
}

IModelFieldExecutor *Context::mkModelFieldExecutor(
			vsc::dm::ITypeField			*type) {
	return new ModelFieldExecutor(type->name(), type->getDataType());
}

IModelFieldExecutorClaim *Context::mkModelFieldExecutorClaim(
			vsc::dm::ITypeField			*type) {
	return new ModelFieldExecutorClaim(
		type->name(),
		type->getDataType());
}

IModelFieldInOut *Context::mkModelFieldInOut(
			ITypeFieldInOut			*type) {
	return new ModelFieldInOut(type);
}

IModelFieldPool *Context::mkModelFieldPoolType(
			vsc::dm::ITypeField			*type) {
	return new ModelFieldPool(type->name(), type->getDataType());
}

IPoolBindDirective *Context::mkPoolBindDirective(
			PoolBindKind			kind,
			vsc::dm::ITypeExprFieldRef	*pool,
			vsc::dm::ITypeExprFieldRef	*target) {
	return new PoolBindDirective(kind, pool, target);
}

ITypeExecProc *Context::mkTypeExecProc(
            ExecKindT               kind,
            ITypeProcStmtScope      *body) {
    return new TypeExecProc(kind, body);
}

ITypeExprMethodCallStatic *Context::mkTypeExprMethodCallContext(
            IDataTypeFunction                           *target,
            vsc::dm::ITypeExpr                          *context,
            const std::vector<vsc::dm::ITypeExpr *>     &params) {

}

ITypeExprMethodCallStatic *Context::mkTypeExprMethodCallStatic(
            IDataTypeFunction                           *target,
            const std::vector<vsc::dm::ITypeExpr *>     &params) {
    return new TypeExprMethodCallStatic(target, params);
}

ITypeFieldActivity *Context::mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) {
	return new TypeFieldActivity(name, type, owned);
}

ITypeFieldClaim *Context::mkTypeFieldClaim(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_lock) {
	return new TypeFieldClaim(name, type, is_lock);
}

ITypeFieldExecutor *Context::mkTypeFieldExecutor(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					owned) {
	return new TypeFieldExecutor(name, type, owned);
}

ITypeFieldExecutorClaim *Context::mkTypeFieldExecutorClaim(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					owned) {
	return new TypeFieldExecutorClaim(name, type, owned);
}

ITypeFieldInOut *Context::mkTypeFieldInOut(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_input) {
	return new TypeFieldInOut(name, type, is_input);
}

ITypeFieldPool *Context::mkTypeFieldPool(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					own,
			vsc::dm::TypeFieldAttr		attr,
			int32_t					decl_size) {
	return new TypeFieldPool(this, name, type, own, attr, decl_size);
}

ITypeProcStmtAssign *Context::mkTypeProcStmtAssign(
			vsc::dm::ITypeExprFieldRef		*lhs,
			TypeProcStmtAssignOp		op,
			vsc::dm::ITypeExpr				*rhs) {
	return new TypeProcStmtAssign(lhs, op, rhs);
}

ITypeProcStmtBreak *Context::mkTypeProcStmtBreak() { 
	return new TypeProcStmtBreak();
}

ITypeProcStmtContinue *Context::mkTypeProcStmtContinue() { 
	return new TypeProcStmtContinue();
}

ITypeProcStmtExpr *Context::mkTypeProcStmtExpr(
            vsc::dm::ITypeExpr *e) {
    return new TypeProcStmtExpr(e);
}

ITypeProcStmtForeach *Context::mkTypeProcStmtForeach(
			vsc::dm::ITypeExpr		*target,
			ITypeProcStmt		*body) { 

}

ITypeProcStmtIfElse *Context::mkTypeProcStmtIfElse(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*true_s,
			ITypeProcStmt		*false_s) { 
	return new TypeProcStmtIfElse(cond, true_s, false_s);
}
	
ITypeProcStmtMatch *Context::mkTypeProcStmtMatch(
			vsc::dm::ITypeExpr		*cond) { 
	return new TypeProcStmtMatch(cond);
}

ITypeProcStmtRepeat *Context::mkTypeProcStmtRepeat(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) { 

}

ITypeProcStmtRepeatWhile *Context::mkTypeProcStmtRepeatWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) { 

}

ITypeProcStmtReturn *Context::mkTypeProcStmtReturn(
			vsc::dm::ITypeExpr		*expr) { 
	return new TypeProcStmtReturn(expr);
}

ITypeProcStmtScope *Context::mkTypeProcStmtScope() { 
	return new TypeProcStmtScope();
}

ITypeProcStmtVarDecl *Context::mkTypeProcStmtVarDecl(
			const std::string	 &name,
			vsc::dm::IDataType		 *type,
			bool				 own,
			vsc::dm::ITypeExpr		 *init) { 
	return new TypeProcStmtVarDecl(name, type, own, init);
}

ITypeProcStmtWhile *Context::mkTypeProcStmtWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) { 

}

}
}
}
