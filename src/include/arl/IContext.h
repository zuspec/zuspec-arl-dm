/*
 * IContext.h
 *
 *  Created on: Apr 2, 2022
 *      Author: mballance
 */
#pragma once
#include "vsc/IContext.h"
#include "arl/IDataTypeAction.h"
#include "arl/IDataTypeActivityParallel.h"
#include "arl/IDataTypeActivitySchedule.h"
#include "arl/IDataTypeActivitySequence.h"
#include "arl/IDataTypeActivityTraverse.h"
#include "arl/IDataTypeAction.h"
#include "arl/IDataTypeComponent.h"
#include "arl/IDataTypeFlowObj.h"
#include "arl/IDataTypeFunction.h"
#include "arl/IDataTypeFunctionParamDecl.h"
#include "arl/IModelActivityParallel.h"
#include "arl/IModelActivitySchedule.h"
#include "arl/IModelActivitySequence.h"
#include "arl/IModelActivityTraverse.h"
#include "arl/IModelEvaluator.h"
#include "arl/IModelFieldAction.h"
#include "arl/IModelFieldComponent.h"
#include "arl/IModelFieldExecutor.h"
#include "arl/IModelFieldExecutorClaim.h"
#include "arl/ITypeFieldClaim.h"
#include "arl/ITypeFieldExecutor.h"
#include "arl/ITypeFieldExecutorClaim.h"
#include "arl/ITypeFieldInOut.h"
#include "arl/ITypeFieldPool.h"
#include "arl/ITypeProcStmtAssign.h"
#include "arl/ITypeProcStmtBreak.h"
#include "arl/ITypeProcStmtContinue.h"
#include "arl/ITypeProcStmtForeach.h"
#include "arl/ITypeProcStmtIfElse.h"
#include "arl/ITypeProcStmtMatch.h"
#include "arl/ITypeProcStmtRepeat.h"
#include "arl/ITypeProcStmtRepeatWhile.h"
#include "arl/ITypeProcStmtReturn.h"
#include "arl/ITypeProcStmtScope.h"
#include "arl/ITypeProcStmtVarDecl.h"
#include "arl/ITypeProcStmtWhile.h"

namespace arl {

class IContext;
using IContextUP=std::unique_ptr<IContext>;
class IContext : public virtual vsc::IContext {
public:

	virtual ~IContext() { }

	virtual IModelFieldAction *buildModelAction(
			IDataTypeAction 	*t,
			const std::string	&name) = 0;

	virtual IModelFieldComponent *buildModelComponent(
			IDataTypeComponent 	*t,
			const std::string	&name) = 0;

	virtual IDataTypeAction *findDataTypeAction(const std::string &name) = 0;

	virtual IDataTypeAction *mkDataTypeAction(const std::string &name) = 0;

	virtual bool addDataTypeAction(IDataTypeAction *t) = 0;

	virtual IDataTypeFunction *findDataTypeFunction(const std::string &name) = 0;

	virtual IDataTypeFunction *mkDataTypeFunction(
			const std::string		&name,
			vsc::IDataType			*rtype,
			bool					own_rtype) = 0;

	virtual IDataTypeFunctionParamDecl *mkDataTypeFunctionParamDecl(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					own,
			vsc::ITypeExpr			*init) = 0;

	virtual bool addDataTypeFunction(IDataTypeFunction *f) = 0;

	virtual IDataTypeActivityParallel *mkDataTypeActivityParallel() = 0;

	virtual IDataTypeActivitySchedule *mkDataTypeActivitySchedule() = 0;

	virtual IDataTypeActivitySequence *mkDataTypeActivitySequence() = 0;

	virtual IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
			vsc::ITypeExprFieldRef 		*target,
			vsc::ITypeConstraint		*with_c) = 0;

	virtual IDataTypeComponent *findDataTypeComponent(const std::string &name) = 0;

	virtual IDataTypeComponent *mkDataTypeComponent(const std::string &name) = 0;

	virtual bool addDataTypeComponent(IDataTypeComponent *t) = 0;

	virtual IDataTypeFlowObj *findDataTypeFlowObj(
			const std::string 	&name, 
			FlowObjKindE 		kind) = 0;

	virtual IDataTypeFlowObj *mkDataTypeFlowObj(
			const std::string 	&name,
			FlowObjKindE		kind) = 0;

	virtual bool addDataTypeFlowObj(IDataTypeFlowObj *t) = 0;

	virtual IModelActivityParallel *mkModelActivityParallel() = 0;

	virtual IModelActivitySchedule *mkModelActivitySchedule() = 0;

	virtual IModelActivitySequence *mkModelActivitySequence() = 0;

	virtual IModelActivityTraverse *mkModelActivityTraverse(
			IModelFieldAction		*target,
			vsc::IModelConstraint	*with_c) = 0;

	virtual IModelEvaluator *mkModelEvaluator(
			ModelEvaluatorKind		kind) = 0;

	virtual IModelFieldAction *mkModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type) = 0;

	virtual IModelFieldAction *mkModelFieldActionType(
			vsc::ITypeField			*type) = 0;

	virtual IModelFieldComponent *mkModelFieldComponentRoot(
			IDataTypeComponent		*type,
			const std::string		&name) = 0;

	virtual IModelFieldComponent *mkModelFieldComponentType(
			vsc::ITypeField			*type) = 0;

	virtual IModelFieldExecutor *mkModelFieldExecutor(
			vsc::ITypeField			*type) = 0;

	virtual IModelFieldExecutorClaim *mkModelFieldExecutorClaim(
			vsc::ITypeField			*type) = 0;

	virtual IModelFieldPool *mkModelFieldPoolType(
			vsc::ITypeField			*type) = 0;

	virtual IPoolBindDirective *mkPoolBindDirective(
			PoolBindKind				kind,
			vsc::ITypeExprFieldRef		*pool,
			vsc::ITypeExprFieldRef		*target) = 0;

	virtual ITypeFieldActivity *mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) = 0;

	virtual ITypeFieldClaim *mkTypeFieldClaim(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_lock) = 0;

	virtual ITypeFieldExecutor *mkTypeFieldExecutor(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					owned) = 0;

	virtual ITypeFieldExecutorClaim *mkTypeFieldExecutorClaim(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					owned) = 0;

	virtual ITypeFieldInOut *mkTypeFieldInOut(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_input) = 0;

	virtual ITypeFieldPool *mkTypeFieldPool(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					own,
			vsc::TypeFieldAttr		attr,
			int32_t					decl_size) = 0;

	virtual ITypeProcStmtAssign *mkTypeProcStmtAssign(
			vsc::ITypeExprFieldRef		*lhs,
			TypeProcStmtAssignOp		op,
			vsc::ITypeExpr				*rhs) = 0;

	virtual ITypeProcStmtBreak *mkTypeProcStmtBreak() = 0;

	virtual ITypeProcStmtContinue *mkTypeProcStmtContinue() = 0;

	virtual ITypeProcStmtForeach *mkTypeProcStmtForeach(
			vsc::ITypeExpr		*target,
			ITypeProcStmt		*body) = 0;

	virtual ITypeProcStmtIfElse *mkTypeProcStmtIfElse(
			vsc::ITypeExpr		*cond,
			ITypeProcStmt		*true_s,
			ITypeProcStmt		*false_s) = 0;
	
	virtual ITypeProcStmtMatch *mkTypeProcStmtMatch(
			vsc::ITypeExpr		*cond) = 0;

	virtual ITypeProcStmtRepeat *mkTypeProcStmtRepeat(
			vsc::ITypeExpr		*cond,
			ITypeProcStmt		*body) = 0;

	virtual ITypeProcStmtRepeatWhile *mkTypeProcStmtRepeatWhile(
			vsc::ITypeExpr		*cond,
			ITypeProcStmt		*body) = 0;

	virtual ITypeProcStmtReturn *mkTypeProcStmtReturn(
			vsc::ITypeExpr		*expr) = 0;

	virtual ITypeProcStmtScope *mkTypeProcStmtScope() = 0;

	virtual ITypeProcStmtVarDecl *mkTypeProcStmtVarDecl(
			const std::string	 &name,
			vsc::IDataType		 *type,
			bool				 own,
			vsc::ITypeExpr		 *init) = 0;

	virtual ITypeProcStmtWhile *mkTypeProcStmtWhile(
			vsc::ITypeExpr		*cond,
			ITypeProcStmt		*body) = 0;

};

}
