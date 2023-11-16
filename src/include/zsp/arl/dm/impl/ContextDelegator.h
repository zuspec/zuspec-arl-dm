/**
 * ContextDelegator.h
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
#pragma once
#include "vsc/dm/impl/ContextDelegator.h"
#include "zsp/arl/dm/IContext.h"

namespace zsp {
namespace arl {
namespace dm {


class ContextDelegator :
    public virtual IContext,
    public virtual vsc::dm::ContextDelegator {
public:

    ContextDelegator(IContext *ctxt, bool owned=true) :
        vsc::dm::ContextDelegator(ctxt, owned) { }

    virtual ~ContextDelegator() { }

    virtual vsc::dm::IValOps *getValOps(DataTypeKind kind) override {
        return ctxt()->getValOps(kind);
    }

    virtual void setValOps(DataTypeKind kind, vsc::dm::IValOps *ops, bool owned=true) {
        ctxt()->setValOps(kind, ops, owned);
    }

    virtual vsc::dm::IDataType *getDataTypeCoreArl(DataTypeCoreE t) override {
        return ctxt()->getDataTypeCoreArl(t);
    }

	virtual IDataTypeAction *findDataTypeAction(const std::string &name) override { 
        return ctxt()->findDataTypeAction(name);
    }

	virtual IDataTypeAction *mkDataTypeAction(const std::string &name) override { 
        return ctxt()->mkDataTypeAction(name);
    }

	virtual bool addDataTypeAction(IDataTypeAction *t) override { 
        return ctxt()->addDataTypeAction(t);
    }

	virtual IDataTypeFunction *findDataTypeFunction(const std::string &name) override { 
        return ctxt()->findDataTypeFunction(name);
    }

	virtual IDataTypeFunction *mkDataTypeFunction(
			const std::string		&name,
			vsc::dm::IDataType		*rtype,
			bool					own_rtype,
            DataTypeFunctionFlags   flags) override {
        return ctxt()->mkDataTypeFunction(name, rtype, own_rtype, flags);
    }
    
    virtual IDataTypeFunctionImport *mkDataTypeFunctionImport(
            const std::string       &lang,
            bool                    is_target,
            bool                    is_solve) { 
        return ctxt()->mkDataTypeFunctionImport(lang, is_target, is_solve);
    }

	virtual IDataTypeFunctionParamDecl *mkDataTypeFunctionParamDecl(
			const std::string		&name,
            ParamDir                dir,
			vsc::dm::IDataType		*type,
			bool					own,
			vsc::dm::ITypeExpr		*init) { 
        return ctxt()->mkDataTypeFunctionParamDecl(
            name, dir, type, own, init
        );
    }

	virtual bool addDataTypeFunction(IDataTypeFunction *f) { 
        return ctxt()->addDataTypeFunction(f);
    }

    virtual const std::vector<IDataTypeFunction *> &getDataTypeFunctions() const override {
        return ctxt()->getDataTypeFunctions();
    }

	virtual IDataTypeActivityParallel *mkDataTypeActivityParallel() { 
        return ctxt()->mkDataTypeActivityParallel();
    }

	virtual IDataTypeActivityReplicate *mkDataTypeActivityReplicate(
			vsc::dm::ITypeExpr			*count) { 
        return ctxt()->mkDataTypeActivityReplicate(count);
    }

	virtual IDataTypeActivitySchedule *mkDataTypeActivitySchedule() { 
        return ctxt()->mkDataTypeActivitySchedule();
    }

	virtual IDataTypeActivitySequence *mkDataTypeActivitySequence() { 
        return ctxt()->mkDataTypeActivitySequence();
    }

	virtual IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
			vsc::dm::ITypeExprFieldRef 		*target,
			vsc::dm::ITypeConstraint		*with_c) { 
        return ctxt()->mkDataTypeActivityTraverse(target, with_c);
    }

	virtual IDataTypeComponent *findDataTypeComponent(const std::string &name) { 
        return ctxt()->findDataTypeComponent(name);
    }

	virtual IDataTypeComponent *mkDataTypeComponent(const std::string &name) { 
        return ctxt()->mkDataTypeComponent(name);
    }

	virtual bool addDataTypeComponent(IDataTypeComponent *t) { 
        return ctxt()->addDataTypeComponent(t);
    }

	virtual IDataTypeFlowObj *findDataTypeFlowObj(
			const std::string 	&name, 
			FlowObjKindE 		kind) { 
        return ctxt()->findDataTypeFlowObj(name, kind);
    }

	virtual IDataTypeFlowObj *mkDataTypeFlowObj(
			const std::string 	&name,
			FlowObjKindE		kind) { 
        return ctxt()->mkDataTypeFlowObj(name, kind);
    }

	virtual bool addDataTypeFlowObj(IDataTypeFlowObj *t) { 
        return ctxt()->addDataTypeFlowObj(t);
    }

    virtual IDataTypePackedStruct *findDataTypePackedStruct(
            const std::string   &name) {
        return ctxt()->findDataTypePackedStruct(name);
    }

    virtual IDataTypePackedStruct *mkDataTypePackedStruct(
            const std::string   &name,
            Endian              endian=Endian::Little) override {
        return ctxt()->mkDataTypePackedStruct(name, endian);
    }

    virtual bool addDataTypePackedStruct(
            IDataTypePackedStruct   *type) override {
        return ctxt()->addDataTypePackedStruct(type);
    }

	virtual IModelActivityParallel *mkModelActivityParallel() { 
        return ctxt()->mkModelActivityParallel();
    }

	virtual IModelActivityReplicate *mkModelActivityReplicate(
			vsc::dm::IModelExpr			*count) { 
        return ctxt()->mkModelActivityReplicate(count);
    }

	virtual IModelActivitySchedule *mkModelActivitySchedule() { 
        return ctxt()->mkModelActivitySchedule();
    }

	virtual IModelActivityScope *mkModelActivityScope(ModelActivityScopeT t) { 
        return ctxt()->mkModelActivityScope(t);
    }

	virtual IModelActivitySequence *mkModelActivitySequence() { 
        return ctxt()->mkModelActivitySequence();
    }

	virtual IModelActivityTraverse *mkModelActivityTraverse(
			IModelFieldAction		*target,
			vsc::dm::IModelConstraint	*with_c,
			bool					own_with_c,
			IModelActivity			*activity,
			bool					owned) { 
        return ctxt()->mkModelActivityTraverse(target, with_c, own_with_c, activity, owned);
    }

    virtual IModelEvalIterator *mkModelEvalIterator(
            IModelActivityScope     *activity) { 
        return ctxt()->mkModelEvalIterator(activity);
    }

	virtual IModelFieldAction *mkModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type) { 
        return ctxt()->mkModelFieldActionRoot(name, type);
    }

	virtual IModelFieldAction *mkModelFieldActionType(
			vsc::dm::ITypeField			*type) { 
        return ctxt()->mkModelFieldActionType(type);
    }

	virtual IModelFieldClaim *mkModelFieldClaim(
			ITypeFieldClaim			*type) { 
        return ctxt()->mkModelFieldClaim(type);
    }

	virtual IModelFieldComponent *mkModelFieldComponentRoot(
			IDataTypeComponent		*type,
			const std::string		&name,
            const vsc::dm::ValRef   &val) { 
        return ctxt()->mkModelFieldComponentRoot(type, name, val);
    }

	virtual IModelFieldComponent *mkModelFieldComponentType(
			vsc::dm::ITypeField			*type) { 
        return ctxt()->mkModelFieldComponentType(type);
    }

	virtual IModelFieldExecutor *mkModelFieldExecutor(
			vsc::dm::ITypeField			*type) { 
        return ctxt()->mkModelFieldExecutor(type);
    }

	virtual IModelFieldExecutorClaim *mkModelFieldExecutorClaim(
			vsc::dm::ITypeField			*type) { 
        return ctxt()->mkModelFieldExecutorClaim(type);
    }

	virtual IModelFieldInOut *mkModelFieldInOut(
			ITypeFieldInOut			*type) { 
        return ctxt()->mkModelFieldInOut(type);
    }

	virtual IModelFieldPool *mkModelFieldPoolType(
			vsc::dm::ITypeField			*type) { 
        return ctxt()->mkModelFieldPoolType(type);
    }

	virtual IModelFieldRegGroup *mkModelFieldRegGroup(
			vsc::dm::ITypeField			*type) { 
        return ctxt()->mkModelFieldRegGroup(type);
    }

	virtual IPoolBindDirective *mkPoolBindDirective(
			PoolBindKind				kind,
			vsc::dm::ITypeExprFieldRef		*pool,
			vsc::dm::ITypeExprFieldRef		*target) { 
        return ctxt()->mkPoolBindDirective(kind, pool, target);
    }

    virtual IPyImport *findPyImport(
            const std::string           &path,
            bool                        create=true) override {
        return ctxt()->findPyImport(path, create);
    }

    virtual const std::vector<IPyImportUP> &getPyImports() const override {
        return ctxt()->getPyImports();
    }

    virtual IPyImport *mkPyImport(
            const std::string           &path) override {
        return ctxt()->mkPyImport(path);
    }

    virtual bool addPyImport(IPyImport *imp) override {
        return ctxt()->addPyImport(imp);
    }

    virtual ITypeExecGroup *mkTypeExecGroup(
            ExecKindT           kind,
            ITypeExecGroup      *super) override {
        return ctxt()->mkTypeExecGroup(kind, super);
    }

    virtual ITypeExecProc *mkTypeExecProc(
            ExecKindT               kind,
            ITypeProcStmtScope      *body) { 
        return ctxt()->mkTypeExecProc(kind, body);
    }

    virtual ITypeExprMethodCallContext *mkTypeExprMethodCallContext(
            IDataTypeFunction                           *target,
            vsc::dm::ITypeExpr                          *context,
            const std::vector<vsc::dm::ITypeExpr *>     &params) { 
        return ctxt()->mkTypeExprMethodCallContext(target, context, params);
    }

    virtual ITypeExprMethodCallStatic *mkTypeExprMethodCallStatic(
            IDataTypeFunction                           *target,
            const std::vector<vsc::dm::ITypeExpr *>     &params) { 
        return ctxt()->mkTypeExprMethodCallStatic(target, params);
    }

    virtual ITypeExprPythonFieldRef *mkTypeExprPythonFieldRef(
        vsc::dm::ITypeExpr      *base,
        bool                    owned,
        const std::string       &name) override {
        return ctxt()->mkTypeExprPythonFieldRef(base, owned, name);
    }

    virtual ITypeExprPythonMethodCall *mkTypeExprPythonMethodCall(
        vsc::dm::ITypeExpr                          *base,
        bool                                        owned,
        const std::string                           &name,
        const std::vector<vsc::dm::ITypeExpr *>     &params) override {
        return ctxt()->mkTypeExprPythonMethodCall(base, owned, name, params);
    }

    virtual ITypeExprPythonModuleRef *mkTypeExprPythonModuleRef(
        IPyImport                                   *imp) override {
        return ctxt()->mkTypeExprPythonModuleRef(imp);
    }

	virtual ITypeFieldActivity *mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) { 
        return ctxt()->mkTypeFieldActivity(name, type, owned);
    }

    virtual ITypeFieldAddrClaim *mkTypeFieldAddrClaim(
            const std::string       &name,
            IDataTypeArlStruct      *trait_t,
            bool                    owned) {
        return ctxt()->mkTypeFieldAddrClaim(name, trait_t, owned);
    }

    virtual ITypeFieldAddrClaimTransparent *mkTypeFieldAddrClaimTransparent(
            const std::string       &name,
            IDataTypeArlStruct      *trait_t,
            bool                    owned) {
        return ctxt()->mkTypeFieldAddrClaimTransparent(name, trait_t, owned);
    }

	virtual ITypeFieldClaim *mkTypeFieldClaim(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_lock) { 
        return ctxt()->mkTypeFieldClaim(name, type, is_lock);
    }

	virtual ITypeFieldExecutor *mkTypeFieldExecutor(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					owned) { 
        return ctxt()->mkTypeFieldExecutor(name, type, owned);
    }

	virtual ITypeFieldExecutorClaim *mkTypeFieldExecutorClaim(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					owned) { 
        return ctxt()->mkTypeFieldExecutorClaim(name, type, owned);
    }

	virtual ITypeFieldInOut *mkTypeFieldInOut(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_input) { 
        return ctxt()->mkTypeFieldInOut(name, type, is_input);
    }

	virtual ITypeFieldPool *mkTypeFieldPool(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					own,
			vsc::dm::TypeFieldAttr		attr,
			int32_t					decl_size) { 
        return ctxt()->mkTypeFieldPool(name, type, own, attr, decl_size);
    }

	virtual ITypeFieldReg *mkTypeFieldReg(
			const std::string		&name,
			vsc::dm::IDataType		*type,
			bool					own) {
        return ctxt()->mkTypeFieldReg(name, type, own);
    }

	virtual ITypeFieldRegGroup *mkTypeFieldRegGroup(
			const std::string		&name,
			vsc::dm::IDataType		*type,
			bool					own) {
        return ctxt()->mkTypeFieldRegGroup(name, type, own);
    }

	virtual ITypeProcStmtAssign *mkTypeProcStmtAssign(
			vsc::dm::ITypeExprFieldRef		*lhs,
			TypeProcStmtAssignOp		op,
			vsc::dm::ITypeExpr				*rhs) { 
        return ctxt()->mkTypeProcStmtAssign(lhs, op, rhs);
    }

	virtual ITypeProcStmtBreak *mkTypeProcStmtBreak() { 
        return ctxt()->mkTypeProcStmtBreak();
    }

	virtual ITypeProcStmtContinue *mkTypeProcStmtContinue() { 
        return ctxt()->mkTypeProcStmtContinue();
    }

	virtual ITypeProcStmtExpr *mkTypeProcStmtExpr(vsc::dm::ITypeExpr *e) { 
        return ctxt()->mkTypeProcStmtExpr(e);
    }

	virtual ITypeProcStmtForeach *mkTypeProcStmtForeach(
			vsc::dm::ITypeExpr		*target,
			ITypeProcStmt		*body) { 
        return ctxt()->mkTypeProcStmtForeach(target, body);
    }

	virtual ITypeProcStmtIfElse *mkTypeProcStmtIfElse(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*true_s,
			ITypeProcStmt		*false_s) { 
        return ctxt()->mkTypeProcStmtIfElse(cond, true_s, false_s);
    }
	
	virtual ITypeProcStmtMatch *mkTypeProcStmtMatch(
			vsc::dm::ITypeExpr		*cond) { 
        return ctxt()->mkTypeProcStmtMatch(cond);
    }

	virtual ITypeProcStmtRepeat *mkTypeProcStmtRepeat(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) { 
        return ctxt()->mkTypeProcStmtRepeat(cond, body);
    }

	virtual ITypeProcStmtRepeatWhile *mkTypeProcStmtRepeatWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) { 
        return ctxt()->mkTypeProcStmtRepeatWhile(cond, body);
    }

	virtual ITypeProcStmtReturn *mkTypeProcStmtReturn(vsc::dm::ITypeExpr *expr) { 
        return ctxt()->mkTypeProcStmtReturn(expr);
    }

	virtual ITypeProcStmtScope *mkTypeProcStmtScope() { 
        return ctxt()->mkTypeProcStmtScope();
    }

	virtual ITypeProcStmtScope *mkTypeProcStmtScope(const std::vector<ITypeProcStmt *> &stmts) { 
        return ctxt()->mkTypeProcStmtScope(stmts);
    }

	virtual ITypeProcStmtVarDecl *mkTypeProcStmtVarDecl(
			const std::string	 &name,
			vsc::dm::IDataType		 *type,
			bool				 own,
			vsc::dm::ITypeExpr		 *init) { 
        return ctxt()->mkTypeProcStmtVarDecl(name, type, own, init);
    }

	virtual ITypeProcStmtWhile *mkTypeProcStmtWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) override { 
        return ctxt()->mkTypeProcStmtWhile(cond, body);
    }

    virtual ValRefPyObj mkValPyObj(pyapi::PyEvalObj *obj) override {
        return ctxt()->mkValPyObj(obj);
    }

protected:
    IContext *ctxt() const { return dynamic_cast<IContext *>(m_ctxt.get()); }

};

}
}
}


