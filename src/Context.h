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

    virtual vsc::dm::IValOps *getValOps(DataTypeKind kind) override;

    virtual void setValOps(DataTypeKind kind, vsc::dm::IValOps *ops, bool owned=true) override;

    virtual vsc::dm::IDataType *getDataTypeCoreArl(DataTypeCoreE t) override;

	virtual IDataTypeAction *findDataTypeAction(const std::string &) override;

	virtual IDataTypeAction *mkDataTypeAction(const std::string &name) override;

    virtual IDataTypeAddrClaim *mkDataTypeAddrClaim(const std::string &name) override;

    virtual IDataTypeAddrClaimTransparent *mkDataTypeAddrClaimTransparent(const std::string &name) override;

    virtual IDataTypeAddrHandle *mkDataTypeAddrHandle(const std::string &name) override;

	virtual IDataTypeAddrSpaceC *mkDataTypeAddrSpaceC(
        const std::string           &name,
        vsc::dm::IDataTypeStruct    *trait_t) override;

    virtual vsc::dm::IDataTypeStruct *mkDataTypeStruct(
        const std::string           &name) override;

	virtual bool addDataTypeAction(IDataTypeAction *t) override;

	virtual IDataTypeAddrSpaceTransparentC *mkDataTypeAddrSpaceTransparentC(
        const std::string           &name,
        vsc::dm::IDataTypeStruct    *trait_t) override;

	virtual IDataTypeFunction *findDataTypeFunction(const std::string &name) override;

	virtual IDataTypeFunction *mkDataTypeFunction(
			const std::string		    &name,
			vsc::dm::IDataType			*rtype,
			bool					    own_rtype,
            DataTypeFunctionFlags       flags) override;

	virtual bool addDataTypeFunction(IDataTypeFunction *f) override;

    virtual const std::vector<IDataTypeFunction *> &getDataTypeFunctions() const override;

    virtual IDataTypeFunctionImport *mkDataTypeFunctionImport(
            const std::string       &lang,
            bool                    is_target,
            bool                    is_solve) override;

	virtual IDataTypeFunctionParamDecl *mkDataTypeFunctionParamDecl(
			const std::string		&name,
            ParamDir                dir,
			vsc::dm::IDataType		*type,
			bool					own,
			vsc::dm::ITypeExpr		*dflt) override;

    virtual IDataTypeRegGroup *mkDataTypeRegGroup(const std::string &name) override;

	virtual IDataTypeActivityParallel *mkDataTypeActivityParallel() override;

	virtual IDataTypeActivityReplicate *mkDataTypeActivityReplicate(
			vsc::dm::ITypeExpr			*count) override;

	virtual IDataTypeActivitySchedule *mkDataTypeActivitySchedule() override;

	virtual IModelActivityScope *mkModelActivityScope(ModelActivityScopeT t) override;

	virtual IDataTypeActivitySequence *mkDataTypeActivitySequence() override;

	virtual IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
			vsc::dm::ITypeExpr	        *target,
			vsc::dm::ITypeConstraint	*with_c) override;

	virtual IDataTypeActivityTraverseType *mkDataTypeActivityTraverseType(
            arl::dm::IDataTypeAction        *target,
			vsc::dm::ITypeConstraint		*with_c) override;

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

    virtual IDataTypePackedStruct *findDataTypePackedStruct(
            const std::string   &name) override;

    virtual IDataTypePackedStruct *mkDataTypePackedStruct(
            const std::string   &name,
            Endian              endian=Endian::Little) override;

    virtual bool addDataTypePackedStruct(
            IDataTypePackedStruct   *type) override;

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
			const std::string		&name,
            const vsc::dm::ValRef   &val) override;

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

	virtual IModelFieldRegGroup *mkModelFieldRegGroup(
            vsc::dm::ITypeField         *type) override;

	virtual IPoolBindDirective *mkPoolBindDirective(
			PoolBindKind			kind,
			vsc::dm::ITypeExprFieldRef	*pool,
			vsc::dm::ITypeExprFieldRef	*target) override;

    virtual IPyImport *findPyImport(
            const std::string           &path,
            bool                        create=true) override;

    virtual const std::vector<IPyImportUP> &getPyImports() const override;

    virtual IPyImport *mkPyImport(
            const std::string           &path) override;

    virtual bool addPyImport(IPyImport *imp) override;

    virtual ITypeExecGroup *mkTypeExecGroup(
            ExecKindT           kind,
            ITypeExecGroup      *super) override;

    virtual ITypeExecProc *mkTypeExecProc(
            ExecKindT               kind,
            ITypeProcStmtScope      *body) override;

    virtual ITypeExprMethodCallContext *mkTypeExprMethodCallContext(
            IDataTypeFunction                           *target,
            vsc::dm::ITypeExpr                          *context,
            const std::vector<vsc::dm::ITypeExpr *>     &params,
            bool                                        owned=true) override;

    virtual ITypeExprMethodCallStatic *mkTypeExprMethodCallStatic(
            IDataTypeFunction                           *target,
            const std::vector<vsc::dm::ITypeExpr *>     &params,
            bool                                        owned=true) override;

    virtual ITypeExprPyImportRef *mkTypeExprPyImportRef(
            IPyImport                                   *imp) override;

    virtual ITypeExprPythonFieldRef *mkTypeExprPythonFieldRef(
        vsc::dm::ITypeExpr      *base,
        bool                    owned,
        const std::string       &name) override;

    virtual ITypeExprPythonMethodCall *mkTypeExprPythonMethodCall(
        vsc::dm::ITypeExpr                          *base,
        bool                                        owned,
        const std::vector<vsc::dm::ITypeExpr *>     &params) override;

    virtual ITypeExprPythonModuleRef *mkTypeExprPythonModuleRef(
        IPyImport                                   *imp) override;

	virtual ITypeFieldActivity *mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) override;

    virtual ITypeFieldAddrClaim *mkTypeFieldAddrClaim(
            const std::string           &name,
            vsc::dm::IDataType          *type,
            bool                        owned,
            vsc::dm::IDataTypeStruct    *trait_t) override;

    virtual ITypeFieldAddrClaimTransparent *mkTypeFieldAddrClaimTransparent(
            const std::string           &name,
            vsc::dm::IDataType          *type,
            bool                        owned,
            vsc::dm::IDataTypeStruct    *trait_t) override;

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

    virtual ITypeFieldReg *mkTypeFieldReg(
            const std::string       &name,
            vsc::dm::IDataType      *type,
            bool                    own) override;

    virtual ITypeFieldRegGroup *mkTypeFieldRegGroup(
            const std::string       &name,
            vsc::dm::IDataType      *type,
            bool                    own) override;

    virtual ITypeFieldRegGroupArr *mkTypeFieldRegGroupArr(
            const std::string       &name,
            vsc::dm::IDataType      *type,
            bool                    own_type,
            vsc::dm::IDataType      *elem_type,
            bool                    own_elem_type,
            int32_t                 size) override;

	virtual ITypeProcStmtAssign *mkTypeProcStmtAssign(
			vsc::dm::ITypeExpr		*lhs,
			TypeProcStmtAssignOp	op,
			vsc::dm::ITypeExpr		*rhs) override;

	virtual ITypeProcStmtBreak *mkTypeProcStmtBreak() override;

	virtual ITypeProcStmtContinue *mkTypeProcStmtContinue() override;

	virtual ITypeProcStmtExpr *mkTypeProcStmtExpr(
            vsc::dm::ITypeExpr *e) override;

	virtual ITypeProcStmtForeach *mkTypeProcStmtForeach(
			vsc::dm::ITypeExpr		*target,
			ITypeProcStmt		*body) override;

	virtual ITypeProcStmtIfClause *mkTypeProcStmtIfClause(
            vsc::dm::ITypeExpr          *cond,
            ITypeProcStmt               *stmt) override;

	virtual ITypeProcStmtIfElse *mkTypeProcStmtIfElse(
        const std::vector<ITypeProcStmtIfClause *>      &if_c,
        ITypeProcStmt                                   *else_c) override;
	
	virtual ITypeProcStmtMatch *mkTypeProcStmtMatch(
			vsc::dm::ITypeExpr		*cond) override;

    virtual ITypeProcStmtMatchChoice *mkTypeProcStmtMatchChoice(
            vsc::dm::ITypeExprRangelist     *cond,
            ITypeProcStmt                   *body) override;

	virtual ITypeProcStmtRepeat *mkTypeProcStmtRepeat(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) override;

	virtual ITypeProcStmtRepeatWhile *mkTypeProcStmtRepeatWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) override;

	virtual ITypeProcStmtReturn *mkTypeProcStmtReturn(
			vsc::dm::ITypeExpr		*expr) override;

	virtual ITypeProcStmtScope *mkTypeProcStmtScope() override;

	virtual ITypeProcStmtScope *mkTypeProcStmtScope(
        const std::vector<ITypeProcStmt *> &stmts
    ) override;

	virtual ITypeProcStmtVarDecl *mkTypeProcStmtVarDecl(
			const std::string	 &name,
			vsc::dm::IDataType		 *type,
			bool				 own,
			vsc::dm::ITypeExpr		 *init) override;

	virtual ITypeProcStmtWhile *mkTypeProcStmtWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		    *body) override;

	virtual ITypeProcStmtYield *mkTypeProcStmtYield() override;

    virtual ValRefPyObj mkValPyObj(pyapi::PyEvalObj *obj) override;

private:
	using FlowObjMapT=std::unordered_map<std::string,IDataTypeFlowObjUP>;

private:
    vsc::dm::UP<vsc::dm::IValOps>                               m_ops[(int)DataTypeKind::NumKinds];
    vsc::dm::UP<vsc::dm::IDataType>                             m_core_types[(int)DataTypeCoreE::NumKinds];
	std::unordered_map<std::string, IDataTypeAction *>			m_action_type_m;
    std::vector<IDataTypeActionUP>                              m_action_type_l;
	std::unordered_map<std::string, IDataTypeComponent *>		m_component_type_m;
    std::vector<IDataTypeComponentUP>                           m_component_type_l;
	std::unordered_map<std::string, IDataTypeFunctionUP>		m_function_type_m;
    std::vector<IDataTypeFunction *>                            m_function_type_l;
	std::unordered_map<FlowObjKindE, FlowObjMapT>				m_flowobj_kind_m;
    std::unordered_map<std::string, IPyImport *>                m_pyimport_m;
    std::vector<IPyImportUP>                                    m_pyimport_l;

};

}
}
}

