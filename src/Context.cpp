/*
 * Context.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */
#include "vsc/dm/impl/ValRef.h"
#include "Context.h"
#include "DataTypeAction.h"
#include "DataTypeActivityBind.h"
#include "DataTypeActivityParallel.h"
#include "DataTypeActivityReplicate.h"
#include "DataTypeActivitySchedule.h"
#include "DataTypeActivitySequence.h"
#include "DataTypeActivityTraverse.h"
#include "DataTypeActivityTraverseType.h"
#include "DataTypeAddrClaim.h"
#include "DataTypeAddrClaimTransparent.h"
#include "DataTypeAddrHandle.h"
#include "DataTypeAddrSpaceC.h"
#include "DataTypeAddrSpaceTransparentC.h"
#include "DataTypeComponent.h"
#include "DataTypeFlowObj.h"
#include "DataTypeFunction.h"
#include "DataTypeFunctionImport.h"
#include "DataTypeFunctionParamDecl.h"
#include "DataTypePackedStruct.h"
#include "DataTypePyObj.h"
#include "DataTypeRegGroup.h"
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
#include "ModelFieldRegGroup.h"
#include "PoolBindDirective.h"
#include "PyImport.h"
#include "TaskBuildModelAction.h"
#include "TaskBuildModelComponent.h"
#include "TaskBuildModelField.h"
#include "TypeExprMethodCallContext.h"
#include "TypeExprMethodCallStatic.h"
#include "TypeExecGroup.h"
#include "TypeExecProc.h"
#include "TypeExprPyImportRef.h"
#include "TypeExprPythonFieldRef.h"
#include "TypeExprPythonMethodCall.h"
#include "TypeExprPythonModuleRef.h"
#include "TypeFieldActivity.h"
#include "TypeFieldAddrClaim.h"
#include "TypeFieldAddrClaimTransparent.h"
#include "TypeFieldClaim.h"
#include "TypeFieldExecutor.h"
#include "TypeFieldExecutorClaim.h"
#include "TypeFieldInOut.h"
#include "TypeFieldPool.h"
#include "TypeFieldReg.h"
#include "TypeFieldRegGroup.h"
#include "TypeFieldRegGroupArr.h"
#include "TypeProcStmtAssign.h"
#include "TypeProcStmtBreak.h"
#include "TypeProcStmtContinue.h"
#include "TypeProcStmtExpr.h"
#include "TypeProcStmtForeach.h"
#include "TypeProcStmtIfClause.h"
#include "TypeProcStmtIfElse.h"
#include "TypeProcStmtMatch.h"
#include "TypeProcStmtMatchChoice.h"
#include "TypeProcStmtRepeat.h"
#include "TypeProcStmtRepeatWhile.h"
#include "TypeProcStmtReturn.h"
#include "TypeProcStmtScope.h"
#include "TypeProcStmtVarDecl.h"
#include "TypeProcStmtWhile.h"
#include "TypeProcStmtYield.h"

namespace zsp {
namespace arl {
namespace dm {


Context::Context(vsc::dm::IContext *ctxt) : vsc::dm::ContextDelegator(ctxt) {
    m_core_types[(int)DataTypeCoreE::PyObj] = new DataTypePyObj(this);
}

Context::~Context() {

}

vsc::dm::IValOps *Context::getValOps(DataTypeKind kind) {
    return m_ops[(int)kind].get();
}

void Context::setValOps(DataTypeKind kind, vsc::dm::IValOps *ops, bool owned) {
    m_ops[(int)kind] = vsc::dm::UP<vsc::dm::IValOps>(ops, owned);
}

vsc::dm::IDataType *Context::getDataTypeCoreArl(DataTypeCoreE t) {
    return m_core_types[(int)t].get();
}

IDataTypeAction *Context::findDataTypeAction(const std::string &name) {
	std::unordered_map<std::string,IDataTypeAction *>::const_iterator it;

	if ((it=m_action_type_m.find(name)) != m_action_type_m.end()) {
		return it->second;
	} else {
		return 0;
	}
}

IDataTypeAction *Context::mkDataTypeAction(const std::string &name) {
	return new DataTypeAction(this, name);
}

IDataTypeAddrClaim *Context::mkDataTypeAddrClaim(const std::string &name) {
    return new DataTypeAddrClaim(name);
}

IDataTypeAddrClaimTransparent *Context::mkDataTypeAddrClaimTransparent(const std::string &name) {
    return new DataTypeAddrClaimTransparent(name);
}

IDataTypeAddrHandle *Context::mkDataTypeAddrHandle(const std::string &name) {
    return new DataTypeAddrHandle(this, name);
}

IDataTypeAddrSpaceC *Context::mkDataTypeAddrSpaceC(
    const std::string           &name,
    vsc::dm::IDataTypeStruct    *trait_t) {
	return new DataTypeAddrSpaceC(this, name, trait_t);
}

IDataTypeAddrSpaceTransparentC *Context::mkDataTypeAddrSpaceTransparentC(
    const std::string           &name,
    vsc::dm::IDataTypeStruct    *trait_t) {
	return new DataTypeAddrSpaceTransparentC(this, name, trait_t);
}

vsc::dm::IDataTypeStruct *Context::mkDataTypeStruct(
        const std::string           &name) {
    return new DataTypeArlStruct(name);
}

bool Context::addDataTypeAction(IDataTypeAction *t) {
	if (m_action_type_m.insert({t->name(), t}).second) {
        m_action_type_l.push_back(IDataTypeActionUP(t));
        return true;
    } else {
        return false;
    }
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
		vsc::dm::IDataType		*rtype,
		bool					own,
        DataTypeFunctionFlags   flags,
		IDataTypeArlStruct		*context) {
	return new DataTypeFunction(this, name, rtype, own, flags, context);
}

bool Context::addDataTypeFunction(IDataTypeFunction *f) {
	if (m_function_type_m.find(f->name()) == m_function_type_m.end()) {
		m_function_type_m.insert({f->name(), IDataTypeFunctionUP(f)});
        m_function_type_l.push_back(f);
		return true;
	} else {
		return false;
	}
}

const std::vector<IDataTypeFunction *> &Context::getDataTypeFunctions() const {
    return m_function_type_l;
}

IDataTypeFunctionImport *Context::mkDataTypeFunctionImport(
            const std::string       &lang,
            bool                    is_target,
            bool                    is_solve) {
    return new DataTypeFunctionImport(lang, is_target, is_solve);
}

IDataTypeFunctionParamDecl *Context::mkDataTypeFunctionParamDecl(
			const std::string		&name,
            ParamDir                dir,
			vsc::dm::IDataType		*type,
			bool					own,
			vsc::dm::ITypeExpr		*dflt) {
	return new DataTypeFunctionParamDecl(name, dir, type, own, dflt);
}

IDataTypeRegGroup *Context::mkDataTypeRegGroup(const std::string &name) {
    return new DataTypeRegGroup(this, name);
}

IDataTypeActivityBind *Context::mkDataTypeActivityBind(
        const std::vector<vsc::dm::ITypeExprFieldRef *> &targets,
        bool owned) {
    return new DataTypeActivityBind(targets, owned);
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
		vsc::dm::ITypeExpr	        *target,
		vsc::dm::ITypeConstraint	*with_c) {
	return new DataTypeActivityTraverse(target, with_c);
}

IDataTypeActivityTraverseType *Context::mkDataTypeActivityTraverseType(
            arl::dm::IDataTypeAction        *target,
			vsc::dm::ITypeConstraint		*with_c) {
    return new DataTypeActivityTraverseType(target, with_c);
}

IDataTypeComponent *Context::findDataTypeComponent(const std::string &name) {
	std::unordered_map<std::string,IDataTypeComponent *>::const_iterator it;

	if ((it=m_component_type_m.find(name)) != m_component_type_m.end()) {
		return it->second;
	} else {
		return 0;
	}
}

IDataTypeComponent *Context::mkDataTypeComponent(const std::string &name) {
	return new DataTypeComponent(this, name);
}

bool Context::addDataTypeComponent(IDataTypeComponent *t) {
	std::unordered_map<std::string,IDataTypeComponent *>::const_iterator it;

	if ((it=m_component_type_m.find(t->name())) == m_component_type_m.end()) {
        t->finalize(this);
		m_component_type_m.insert({t->name(), t});
        m_component_type_l.push_back(IDataTypeComponentUP(t));
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

IDataTypePackedStruct *Context::findDataTypePackedStruct(
            const std::string   &name) {
    return 0;
}

IDataTypePackedStruct *Context::mkDataTypePackedStruct(
            const std::string   &name,
            Endian              endian) {
    return new DataTypePackedStruct(name, endian);
}

bool Context::addDataTypePackedStruct(
            IDataTypePackedStruct   *type) {
    return true;
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
			const std::string		&name,
            const vsc::dm::ValRef   &val) {
	return new ModelFieldComponentRoot(this, name, type, val);
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

IModelFieldRegGroup *Context::mkModelFieldRegGroup(
            vsc::dm::ITypeField         *type) {
    return new ModelFieldRegGroup(
        type->name(),
        type->getDataType());
}

IPyImport *Context::findPyImport(
            const std::string           &path,
            bool                        create) {
    std::unordered_map<std::string,IPyImport *>::iterator it;
    IPyImport *ret = 0;

    if ((it=m_pyimport_m.find(path)) != m_pyimport_m.end()) {
        ret = it->second;
    } else if (create) {
        ret = new PyImport(path);
        m_pyimport_m.insert({path, ret});
        m_pyimport_l.push_back(IPyImportUP(ret));
    }
    return ret;
}

const std::vector<IPyImportUP> &Context::getPyImports() const {
    return m_pyimport_l;
}

IPyImport *Context::mkPyImport(
            const std::string           &path) {
    return new PyImport(path);
}

bool Context::addPyImport(IPyImport *imp) {
    std::unordered_map<std::string,IPyImport *>::iterator it;
    if ((it=m_pyimport_m.find(imp->path())) == m_pyimport_m.end()) {
        m_pyimport_m.insert({imp->path(), imp});
        m_pyimport_l.push_back(IPyImportUP(imp));
        return true;
    } else {
        return false;
    }
}

ITypeExecGroup *Context::mkTypeExecGroup(
        ExecKindT           kind,
        ITypeExecGroup      *super) {
    return new TypeExecGroup(kind, super);
}

ITypeExecProc *Context::mkTypeExecProc(
            ExecKindT               kind,
            ITypeProcStmtScope      *body) {
    return new TypeExecProc(kind, body);
}

ITypeExprMethodCallContext *Context::mkTypeExprMethodCallContext(
            IDataTypeFunction                           *target,
            vsc::dm::ITypeExpr                          *context,
            const std::vector<vsc::dm::ITypeExpr *>     &params,
            bool                                        owned) {
    return new TypeExprMethodCallContext(target, context, params, owned);
}

ITypeExprMethodCallStatic *Context::mkTypeExprMethodCallStatic(
            IDataTypeFunction                           *target,
            const std::vector<vsc::dm::ITypeExpr *>     &params,
            bool                                        owned) {
    return new TypeExprMethodCallStatic(target, params, owned);
}

ITypeExprPyImportRef *Context::mkTypeExprPyImportRef(
            IPyImport                                   *imp) {
    return new TypeExprPyImportRef(imp);
}

ITypeExprPythonFieldRef *Context::mkTypeExprPythonFieldRef(
        vsc::dm::ITypeExpr      *base,
        bool                    owned,
        const std::string       &name) {
    return new TypeExprPythonFieldRef(base, owned, name);
}

ITypeExprPythonMethodCall *Context::mkTypeExprPythonMethodCall(
        vsc::dm::ITypeExpr                          *base,
        bool                                        owned,
        const std::vector<vsc::dm::ITypeExpr *>     &params) {
    return new TypeExprPythonMethodCall(base, owned, params);
}

ITypeExprPythonModuleRef *Context::mkTypeExprPythonModuleRef(
        IPyImport                                   *imp) {
    return new TypeExprPythonModuleRef(imp);
}

ITypeFieldActivity *Context::mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) {
	return new TypeFieldActivity(name, type, owned);
}

ITypeFieldAddrClaim *Context::mkTypeFieldAddrClaim(
            const std::string           &name,
            vsc::dm::IDataType          *type,
            bool                        owned,
            vsc::dm::IDataTypeStruct    *trait_t) {
    return new TypeFieldAddrClaim(name, type, owned, trait_t);
}

ITypeFieldAddrClaimTransparent *Context::mkTypeFieldAddrClaimTransparent(
            const std::string           &name,
            vsc::dm::IDataType          *type,
            bool                        owned,
            vsc::dm::IDataTypeStruct    *trait_t) {
    return new TypeFieldAddrClaimTransparent(name, type, owned, trait_t);
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

ITypeFieldReg *Context::mkTypeFieldReg(
            const std::string       &name,
            vsc::dm::IDataType      *type,
            bool                    own) {
    return new TypeFieldReg(name, type, own);
}

ITypeFieldRegGroup *Context::mkTypeFieldRegGroup(
            const std::string       &name,
            vsc::dm::IDataType      *type,
            bool                    own) {
    return new TypeFieldRegGroup(
        name,
        findDataTypeWrapper(findDataTypeInt(false, 64), type, true),
        own);
}

ITypeFieldRegGroupArr *Context::mkTypeFieldRegGroupArr(
    const std::string       &name,
    vsc::dm::IDataType      *type,
    bool                    own_type,
    vsc::dm::IDataType      *elem_type,
    bool                    own_elem_type,
    int32_t                 size) {
    return new TypeFieldRegGroupArr(name, type, own_type, elem_type, own_elem_type, size);
}

ITypeProcStmtAssign *Context::mkTypeProcStmtAssign(
			vsc::dm::ITypeExpr		*lhs,
			TypeProcStmtAssignOp	op,
			vsc::dm::ITypeExpr		*rhs) {
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
    return 0;
}

ITypeProcStmtIfClause *Context::mkTypeProcStmtIfClause(
            vsc::dm::ITypeExpr          *cond,
            ITypeProcStmt               *stmt) {
    return new TypeProcStmtIfClause(cond, stmt);
}

ITypeProcStmtIfElse *Context::mkTypeProcStmtIfElse(
        const std::vector<ITypeProcStmtIfClause *>      &if_c,
        ITypeProcStmt                                   *else_c) {
    return new TypeProcStmtIfElse(if_c, else_c);
}
	
ITypeProcStmtMatch *Context::mkTypeProcStmtMatch(
			vsc::dm::ITypeExpr		*cond) { 
	return new TypeProcStmtMatch(cond);
}

ITypeProcStmtMatchChoice *Context::mkTypeProcStmtMatchChoice(
            vsc::dm::ITypeExprRangelist     *cond,
            ITypeProcStmt                   *body) {
    return new TypeProcStmtMatchChoice(cond, body);
}

ITypeProcStmtRepeat *Context::mkTypeProcStmtRepeat(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		    *body) { 
    return new TypeProcStmtRepeat(cond, body);
}

ITypeProcStmtRepeatWhile *Context::mkTypeProcStmtRepeatWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		    *body) { 
    return new TypeProcStmtRepeatWhile(cond, body);
}

ITypeProcStmtReturn *Context::mkTypeProcStmtReturn(
			vsc::dm::ITypeExpr		*expr) { 
	return new TypeProcStmtReturn(expr);
}

ITypeProcStmtScope *Context::mkTypeProcStmtScope() { 
	return new TypeProcStmtScope(this);
}

ITypeProcStmtScope *Context::mkTypeProcStmtScope(
    const std::vector<ITypeProcStmt *> &stmts) { 
	return new TypeProcStmtScope(this, stmts);
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
			ITypeProcStmt		    *body) { 
    return new TypeProcStmtWhile(cond, body);
}

ITypeProcStmtYield *Context::mkTypeProcStmtYield() {
    return new TypeProcStmtYield();
}

ValRefPyObj Context::mkValPyObj(pyapi::PyEvalObj *obj) {
    return ValRefPyObj(vsc::dm::ValRef(
        reinterpret_cast<uintptr_t>(obj),
        m_core_types[(int)DataTypeCoreE::PyObj].get(),
        vsc::dm::ValRef::Flags::Mutable
    ));
}

}
}
}
