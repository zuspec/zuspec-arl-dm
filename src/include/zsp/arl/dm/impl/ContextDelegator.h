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

	virtual IModelFieldAction *buildModelAction(
			IDataTypeAction 	*t,
			const std::string	&name) { 
        return ctxt()->buildModelAction(t, name);
    }

	virtual IModelFieldComponent *buildModelComponent(
			IDataTypeComponent 	*t,
			const std::string	&name) { 
        return ctxt()->buildModelComponent(t, name);
    }

	virtual IDataTypeAction *findDataTypeAction(const std::string &name) { 
        return ctxt()->findDataTypeAction(name);
    }

	virtual IDataTypeAction *mkDataTypeAction(const std::string &name) { 
        return ctxt()->mkDataTypeAction(name);
    }

	virtual bool addDataTypeAction(IDataTypeAction *t) { 
        return ctxt()->addDataTypeAction(t);
    }

	virtual IDataTypeFunction *findDataTypeFunction(const std::string &name) { 
        return ctxt()->findDataTypeFunction(name);
    }

	virtual IDataTypeFunction *mkDataTypeFunction(
			const std::string		&name,
			vsc::dm::IDataType		*rtype,
			bool					own_rtype) { 
        return ctxt()->mkDataTypeFunction(name, rtype, own_rtype);
    }
    
    virtual IDataTypeFunctionImport *mkDataTypeFunctionImport(
            const std::string       &lang) { 
        return ctxt()->mkDataTypeFunctionImport(lang);
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

	virtual IDataTypeActivityParallel *mkDataTypeActivityParallel() { 
        return ctxt()->mkDataTypeActivityParallel();
    }

	virtual IDataTypeActivityReplicate *mkDataTypeActivityReplicate(
			vsc::dm::ITypeExpr			*count) { 
        return ctxt()->mkDataTypeActivityReplicate(count);
    }

	virtual IDataTypeActivitySchedule *mkDataTypeActivitySchedule() { }

	virtual IDataTypeActivitySequence *mkDataTypeActivitySequence() { }

	virtual IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
			vsc::dm::ITypeExprFieldRef 		*target,
			vsc::dm::ITypeConstraint		*with_c) { }

	virtual IDataTypeComponent *findDataTypeComponent(const std::string &name) { }

	virtual IDataTypeComponent *mkDataTypeComponent(const std::string &name) { }

	virtual bool addDataTypeComponent(IDataTypeComponent *t) { }

	virtual IDataTypeFlowObj *findDataTypeFlowObj(
			const std::string 	&name, 
			FlowObjKindE 		kind) { }

	virtual IDataTypeFlowObj *mkDataTypeFlowObj(
			const std::string 	&name,
			FlowObjKindE		kind) { }

	virtual bool addDataTypeFlowObj(IDataTypeFlowObj *t) { }

    virtual IDataTypePackedStruct *findDataTypePackedStruct(
            const std::string   &name) {

    }

    virtual IDataTypePackedStruct *mkDataTypePackedStruct(
            const std::string   &name,
            Endian              endian=Endian::Little) override {

    }

    virtual bool addDataTypePackedStruct(
            IDataTypePackedStruct   *type) override {

    }

	virtual IModelActivityParallel *mkModelActivityParallel() { }

	virtual IModelActivityReplicate *mkModelActivityReplicate(
			vsc::dm::IModelExpr			*count) { }

	virtual IModelActivitySchedule *mkModelActivitySchedule() { }

	virtual IModelActivityScope *mkModelActivityScope(ModelActivityScopeT t) { }

	virtual IModelActivitySequence *mkModelActivitySequence() { }

	virtual IModelActivityTraverse *mkModelActivityTraverse(
			IModelFieldAction		*target,
			vsc::dm::IModelConstraint	*with_c,
			bool					own_with_c,
			IModelActivity			*activity,
			bool					owned) { }

    virtual IModelEvalIterator *mkModelEvalIterator(
            IModelActivityScope     *activity) { }

	virtual IModelFieldAction *mkModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type) { }

	virtual IModelFieldAction *mkModelFieldActionType(
			vsc::dm::ITypeField			*type) { }

	virtual IModelFieldClaim *mkModelFieldClaim(
			ITypeFieldClaim			*type) { }

	virtual IModelFieldComponent *mkModelFieldComponentRoot(
			IDataTypeComponent		*type,
			const std::string		&name) { }

	virtual IModelFieldComponent *mkModelFieldComponentType(
			vsc::dm::ITypeField			*type) { }

	virtual IModelFieldExecutor *mkModelFieldExecutor(
			vsc::dm::ITypeField			*type) { }

	virtual IModelFieldExecutorClaim *mkModelFieldExecutorClaim(
			vsc::dm::ITypeField			*type) { }

	virtual IModelFieldInOut *mkModelFieldInOut(
			ITypeFieldInOut			*type) { }

	virtual IModelFieldPool *mkModelFieldPoolType(
			vsc::dm::ITypeField			*type) { }

	virtual IPoolBindDirective *mkPoolBindDirective(
			PoolBindKind				kind,
			vsc::dm::ITypeExprFieldRef		*pool,
			vsc::dm::ITypeExprFieldRef		*target) { }

    virtual ITypeExecProc *mkTypeExecProc(
            ExecKindT               kind,
            ITypeProcStmtScope      *body) { }

    virtual ITypeExprMethodCallStatic *mkTypeExprMethodCallContext(
            IDataTypeFunction                           *target,
            vsc::dm::ITypeExpr                          *context,
            const std::vector<vsc::dm::ITypeExpr *>     &params) { }

    virtual ITypeExprMethodCallStatic *mkTypeExprMethodCallStatic(
            IDataTypeFunction                           *target,
            const std::vector<vsc::dm::ITypeExpr *>     &params) { }

	virtual ITypeFieldActivity *mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) { }

	virtual ITypeFieldClaim *mkTypeFieldClaim(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_lock) { }

	virtual ITypeFieldExecutor *mkTypeFieldExecutor(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					owned) { }

	virtual ITypeFieldExecutorClaim *mkTypeFieldExecutorClaim(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					owned) { }

	virtual ITypeFieldInOut *mkTypeFieldInOut(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_input) { }

	virtual ITypeFieldPool *mkTypeFieldPool(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					own,
			vsc::dm::TypeFieldAttr		attr,
			int32_t					decl_size) { }

	virtual ITypeProcStmtAssign *mkTypeProcStmtAssign(
			vsc::dm::ITypeExprFieldRef		*lhs,
			TypeProcStmtAssignOp		op,
			vsc::dm::ITypeExpr				*rhs) { }

	virtual ITypeProcStmtBreak *mkTypeProcStmtBreak() { }

	virtual ITypeProcStmtContinue *mkTypeProcStmtContinue() { }

	virtual ITypeProcStmtExpr *mkTypeProcStmtExpr(
            vsc::dm::ITypeExpr *e) { }

	virtual ITypeProcStmtForeach *mkTypeProcStmtForeach(
			vsc::dm::ITypeExpr		*target,
			ITypeProcStmt		*body) { }

	virtual ITypeProcStmtIfElse *mkTypeProcStmtIfElse(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*true_s,
			ITypeProcStmt		*false_s) { }
	
	virtual ITypeProcStmtMatch *mkTypeProcStmtMatch(
			vsc::dm::ITypeExpr		*cond) { }

	virtual ITypeProcStmtRepeat *mkTypeProcStmtRepeat(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) { }

	virtual ITypeProcStmtRepeatWhile *mkTypeProcStmtRepeatWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) { }

	virtual ITypeProcStmtReturn *mkTypeProcStmtReturn(
			vsc::dm::ITypeExpr		*expr) { }

	virtual ITypeProcStmtScope *mkTypeProcStmtScope() { }

	virtual ITypeProcStmtVarDecl *mkTypeProcStmtVarDecl(
			const std::string	 &name,
			vsc::dm::IDataType		 *type,
			bool				 own,
			vsc::dm::ITypeExpr		 *init) { }

	virtual ITypeProcStmtWhile *mkTypeProcStmtWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) { }

protected:
    IContext *ctxt() const { return dynamic_cast<IContext *>(m_ctxt.get()); }

};

}
}
}


