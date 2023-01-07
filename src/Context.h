/*
 * Context.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <unordered_map>
#include "zsp/arl/dm/IContext.h"
#include "vsc/dm/impl/ContextDelegator.h"

namespace zsp {
namespace arl {
namespace dm {


class Context : public virtual IContext, public vsc::dm::ContextDelegator {
public:
	Context(vsc::dm::IContext *ctxt);

	virtual ~Context();

	virtual IModelFieldAction *buildModelAction(
			IDataTypeAction 	*t,
			const std::string	&name) override;

	virtual IModelFieldComponent *buildModelComponent(
			IDataTypeComponent 	*t,
			const std::string	&name) override;

	virtual IDataTypeAction *findDataTypeAction(const std::string &) override;

	virtual IDataTypeAction *mkDataTypeAction(const std::string &name) override;

	virtual bool addDataTypeAction(IDataTypeAction *t) override;

	virtual IDataTypeFunction *findDataTypeFunction(const std::string &name) override;

	virtual IDataTypeFunction *mkDataTypeFunction(
			const std::string		&name,
			vsc::dm::IDataType			*rtype,
			bool					own_rtype) override;

	virtual bool addDataTypeFunction(IDataTypeFunction *f) override;

	virtual IDataTypeFunctionParamDecl *mkDataTypeFunctionParamDecl(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					own,
			vsc::dm::ITypeExpr			*init) override;

	virtual IDataTypeActivityParallel *mkDataTypeActivityParallel() override;

	virtual IDataTypeActivityReplicate *mkDataTypeActivityReplicate(
			vsc::dm::ITypeExpr			*count) override;

	virtual IDataTypeActivitySchedule *mkDataTypeActivitySchedule() override;

	virtual IModelActivityScope *mkModelActivityScope(ModelActivityScopeT t) override;

	virtual IDataTypeActivitySequence *mkDataTypeActivitySequence() override;

	virtual IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
			vsc::dm::ITypeExprFieldRef	*target,
			vsc::dm::ITypeConstraint	*with_c) override;

	virtual IDataTypeComponent *findDataTypeComponent(const std::string &name) override;

	virtual IDataTypeComponent *mkDataTypeComponent(const std::string &name) override;

	virtual bool addDataTypeComponent(IDataTypeComponent *t) override;

	virtual IDataTypeFlowObj *findDataTypeFlowObj(
			const std::string 	&name,
			FlowObjKindE		kind) override;

	virtual IDataTypeFlowObj *mkDataTypeFlowObj(
			const std::string 	&name,
			FlowObjKindE		kind) override;

	virtual bool addDataTypeFlowObj(IDataTypeFlowObj *t) override;

	virtual IModelActivityParallel *mkModelActivityParallel() override;

	virtual IModelActivityReplicate *mkModelActivityReplicate(
			vsc::dm::IModelExpr			*count) override;

	virtual IModelActivitySchedule *mkModelActivitySchedule() override;

	virtual IModelActivitySequence *mkModelActivitySequence() override;

	virtual IModelActivityTraverse *mkModelActivityTraverse(
			IModelFieldAction		*target,
			vsc::dm::IModelConstraint	*with_c,
			bool					own_with_c,
			IModelActivity			*activity,
			bool					owned) override;

    virtual IModelEvalIterator *mkModelEvalIterator(
            IModelActivityScope     *activity) override;

	virtual IModelFieldAction *mkModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type) override;

	virtual IModelFieldAction *mkModelFieldActionType(
			vsc::dm::ITypeField			*type) override;

	virtual IModelFieldClaim *mkModelFieldClaim(
			ITypeFieldClaim			*type) override;

	virtual IModelFieldComponent *mkModelFieldComponentRoot(
			IDataTypeComponent		*type,
			const std::string		&name) override;

	virtual IModelFieldComponent *mkModelFieldComponentType(
			vsc::dm::ITypeField         *type) override;

	virtual IModelFieldExecutor *mkModelFieldExecutor(
			vsc::dm::ITypeField			*type) override;

	virtual IModelFieldExecutorClaim *mkModelFieldExecutorClaim(
			vsc::dm::ITypeField			*type) override;

	virtual IModelFieldInOut *mkModelFieldInOut(
			ITypeFieldInOut			*type) override;

	virtual IModelFieldPool *mkModelFieldPoolType(
			vsc::dm::ITypeField			*type) override;

	virtual IPoolBindDirective *mkPoolBindDirective(
			PoolBindKind			kind,
			vsc::dm::ITypeExprFieldRef	*pool,
			vsc::dm::ITypeExprFieldRef	*target) override;

	virtual ITypeFieldActivity *mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) override;

	virtual ITypeFieldClaim *mkTypeFieldClaim(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_lock) override;

	virtual ITypeFieldExecutor *mkTypeFieldExecutor(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					owned) override;

	virtual ITypeFieldExecutorClaim *mkTypeFieldExecutorClaim(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					owned) override;

	virtual ITypeFieldInOut *mkTypeFieldInOut(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_input) override;

	virtual ITypeFieldPool *mkTypeFieldPool(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					own,
			vsc::dm::TypeFieldAttr		attr,
			int32_t					decl_size) override;

	virtual ITypeProcStmtAssign *mkTypeProcStmtAssign(
			vsc::dm::ITypeExprFieldRef		*lhs,
			TypeProcStmtAssignOp		op,
			vsc::dm::ITypeExpr				*rhs) override;

	virtual ITypeProcStmtBreak *mkTypeProcStmtBreak() override;

	virtual ITypeProcStmtContinue *mkTypeProcStmtContinue() override;

	virtual ITypeProcStmtForeach *mkTypeProcStmtForeach(
			vsc::dm::ITypeExpr		*target,
			ITypeProcStmt		*body) override;

	virtual ITypeProcStmtIfElse *mkTypeProcStmtIfElse(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*true_s,
			ITypeProcStmt		*false_s) override;
	
	virtual ITypeProcStmtMatch *mkTypeProcStmtMatch(
			vsc::dm::ITypeExpr		*cond) override;

	virtual ITypeProcStmtRepeat *mkTypeProcStmtRepeat(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) override;

	virtual ITypeProcStmtRepeatWhile *mkTypeProcStmtRepeatWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) override;

	virtual ITypeProcStmtReturn *mkTypeProcStmtReturn(
			vsc::dm::ITypeExpr		*expr) override;

	virtual ITypeProcStmtScope *mkTypeProcStmtScope() override;

	virtual ITypeProcStmtVarDecl *mkTypeProcStmtVarDecl(
			const std::string	 &name,
			vsc::dm::IDataType		 *type,
			bool				 own,
			vsc::dm::ITypeExpr		 *init) override;

	virtual ITypeProcStmtWhile *mkTypeProcStmtWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) override;

private:
	using FlowObjMapT=std::unordered_map<std::string,IDataTypeFlowObjUP>;

private:
	std::unordered_map<std::string, IDataTypeActionUP>			m_action_type_m;
	std::unordered_map<std::string, IDataTypeComponentUP>		m_component_type_m;
	std::unordered_map<std::string, IDataTypeFunctionUP>		m_function_type_m;
	std::unordered_map<FlowObjKindE, FlowObjMapT>				m_flowobj_kind_m;

};

}
}
}

