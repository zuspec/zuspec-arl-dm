/*
 * IContext.h
 *
 *  Created on: Apr 2, 2022
 *      Author: mballance
 */
#pragma once
#include "vsc/dm/IContext.h"
#include "zsp/arl/dm/IDataTypeAction.h"
#include "zsp/arl/dm/IDataTypeActivityParallel.h"
#include "zsp/arl/dm/IDataTypeActivitySchedule.h"
#include "zsp/arl/dm/IDataTypeActivitySequence.h"
#include "zsp/arl/dm/IDataTypeActivityTraverse.h"
#include "zsp/arl/dm/IDataTypeAction.h"
#include "zsp/arl/dm/IDataTypeAddrClaim.h"
#include "zsp/arl/dm/IDataTypeAddrClaimTransparent.h"
#include "zsp/arl/dm/IDataTypeAddrHandle.h"
#include "zsp/arl/dm/IDataTypeAddrSpaceC.h"
#include "zsp/arl/dm/IDataTypeAddrSpaceTransparentC.h"
#include "zsp/arl/dm/IDataTypeComponent.h"
#include "zsp/arl/dm/IDataTypeCoreLibComponent.h"
#include "zsp/arl/dm/IDataTypeFlowObj.h"
#include "zsp/arl/dm/IDataTypeFunction.h"
#include "zsp/arl/dm/IDataTypeFunctionImport.h"
#include "zsp/arl/dm/IDataTypeFunctionParamDecl.h"
#include "zsp/arl/dm/IDataTypePackedStruct.h"
#include "zsp/arl/dm/IDataTypeRegGroup.h"
#include "zsp/arl/dm/IModelActivityParallel.h"
#include "zsp/arl/dm/IModelActivitySchedule.h"
#include "zsp/arl/dm/IModelActivityScope.h"
#include "zsp/arl/dm/IModelActivitySequence.h"
#include "zsp/arl/dm/IModelActivityTraverse.h"
#include "zsp/arl/dm/IModelEvalIterator.h"
#include "zsp/arl/dm/IModelFieldAction.h"
#include "zsp/arl/dm/IModelFieldClaim.h"
#include "zsp/arl/dm/IModelFieldComponent.h"
#include "zsp/arl/dm/IModelFieldExecutor.h"
#include "zsp/arl/dm/IModelFieldExecutorClaim.h"
#include "zsp/arl/dm/IModelFieldRegGroup.h"
#include "zsp/arl/dm/IPyImport.h"
#include "zsp/arl/dm/ITypeExecGroup.h"
#include "zsp/arl/dm/ITypeExecProc.h"
#include "zsp/arl/dm/ITypeExprMethodCallContext.h"
#include "zsp/arl/dm/ITypeExprMethodCallStatic.h"
#include "zsp/arl/dm/ITypeExprPyImportRef.h"
#include "zsp/arl/dm/ITypeExprPythonFieldRef.h"
#include "zsp/arl/dm/ITypeExprPythonMethodCall.h"
#include "zsp/arl/dm/ITypeExprPythonModuleRef.h"
#include "zsp/arl/dm/ITypeFieldAddrClaim.h"
#include "zsp/arl/dm/ITypeFieldAddrClaimTransparent.h"
#include "zsp/arl/dm/ITypeFieldClaim.h"
#include "zsp/arl/dm/ITypeFieldExecutor.h"
#include "zsp/arl/dm/ITypeFieldExecutorClaim.h"
#include "zsp/arl/dm/ITypeFieldInOut.h"
#include "zsp/arl/dm/ITypeFieldPool.h"
#include "zsp/arl/dm/ITypeFieldReg.h"
#include "zsp/arl/dm/ITypeFieldRegGroup.h"
#include "zsp/arl/dm/ITypeFieldRegGroupArr.h"
#include "zsp/arl/dm/ITypeProcStmtAssign.h"
#include "zsp/arl/dm/ITypeProcStmtBreak.h"
#include "zsp/arl/dm/ITypeProcStmtContinue.h"
#include "zsp/arl/dm/ITypeProcStmtExpr.h"
#include "zsp/arl/dm/ITypeProcStmtForeach.h"
#include "zsp/arl/dm/ITypeProcStmtIfElse.h"
#include "zsp/arl/dm/ITypeProcStmtMatch.h"
#include "zsp/arl/dm/ITypeProcStmtRepeat.h"
#include "zsp/arl/dm/ITypeProcStmtRepeatWhile.h"
#include "zsp/arl/dm/ITypeProcStmtReturn.h"
#include "zsp/arl/dm/ITypeProcStmtScope.h"
#include "zsp/arl/dm/ITypeProcStmtVarDecl.h"
#include "zsp/arl/dm/ITypeProcStmtWhile.h"
#include "zsp/arl/dm/ITypeProcStmtYield.h"
#include "zsp/arl/dm/impl/ValRefPyObj.h"

namespace zsp {
namespace arl {
namespace dm {

enum class DataTypeKind {
    PyObj,
    NumKinds
};

enum class DataTypeCoreE {
    PyObj,
    NumKinds
};


class IContext;
using IContextUP=vsc::dm::UP<IContext>;
class IContext : public virtual vsc::dm::IContext {
public:

	virtual ~IContext() { }

    virtual vsc::dm::IValOps *getValOps(DataTypeKind kind) = 0;

    virtual void setValOps(DataTypeKind kind, vsc::dm::IValOps *ops, bool owned=true) = 0;

    virtual vsc::dm::IDataType *getDataTypeCoreArl(DataTypeCoreE t) = 0;

	virtual IDataTypeAction *findDataTypeAction(const std::string &name) = 0;

	virtual IDataTypeAction *mkDataTypeAction(const std::string &name) = 0;

    virtual IDataTypeAddrClaim *mkDataTypeAddrClaim(const std::string &name) = 0;

    virtual IDataTypeAddrClaimTransparent *mkDataTypeAddrClaimTransparent(const std::string &name) = 0;

    virtual IDataTypeAddrHandle *mkDataTypeAddrHandle(const std::string &name) = 0;

	virtual IDataTypeAddrSpaceC *mkDataTypeAddrSpaceC(
        const std::string           &name,
        vsc::dm::IDataTypeStruct    *trait_t) = 0;

	virtual IDataTypeAddrSpaceTransparentC *mkDataTypeAddrSpaceTransparentC(
        const std::string           &name,
        vsc::dm::IDataTypeStruct    *trait_t) = 0;

	virtual bool addDataTypeAction(IDataTypeAction *t) = 0;

	virtual IDataTypeFunction *findDataTypeFunction(const std::string &name) = 0;

	virtual IDataTypeFunction *mkDataTypeFunction(
			const std::string		&name,
			vsc::dm::IDataType		*rtype,
			bool					own_rtype,
            DataTypeFunctionFlags   flags=DataTypeFunctionFlags::NoFlags,
			IDataTypeArlStruct		*context=0) = 0;

	virtual bool addDataTypeFunction(IDataTypeFunction *f) = 0;

    virtual const std::vector<IDataTypeFunction *> &getDataTypeFunctions() const = 0;
    
    virtual IDataTypeFunctionImport *mkDataTypeFunctionImport(
            const std::string       &lang,
            bool                    is_target,
            bool                    is_solve) = 0;

	virtual IDataTypeFunctionParamDecl *mkDataTypeFunctionParamDecl(
			const std::string		&name,
            ParamDir                dir,
			vsc::dm::IDataType		*type,
			bool					own,
			vsc::dm::ITypeExpr		*init) = 0;

    virtual IDataTypeRegGroup *mkDataTypeRegGroup(const std::string &name) = 0;

	virtual IDataTypeActivityParallel *mkDataTypeActivityParallel() = 0;

	virtual IDataTypeActivityReplicate *mkDataTypeActivityReplicate(
			vsc::dm::ITypeExpr			*count) = 0;

	virtual IDataTypeActivitySchedule *mkDataTypeActivitySchedule() = 0;

	virtual IDataTypeActivitySequence *mkDataTypeActivitySequence() = 0;

	virtual IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
			vsc::dm::ITypeExpr 		        *target,
			vsc::dm::ITypeConstraint		*with_c) = 0;

	virtual IDataTypeActivityTraverseType *mkDataTypeActivityTraverseType(
            arl::dm::IDataTypeAction        *target,
			vsc::dm::ITypeConstraint		*with_c) = 0;

	virtual IDataTypeComponent *findDataTypeComponent(const std::string &name) = 0;

	virtual IDataTypeComponent *mkDataTypeComponent(const std::string &name) = 0;

	virtual bool addDataTypeComponent(IDataTypeComponent *t) = 0;

	virtual IDataTypeFlowObj *findDataTypeFlowObj(
			const std::string 	&name, 
			FlowObjKindE 		kind) = 0;

	virtual IDataTypeFlowObj *mkDataTypeFlowObj(
			const std::string 	&name,
			FlowObjKindE		kind) = 0;

    template <class T> T *mkDataTypeFlowObjT(
			const std::string 	&name,
			FlowObjKindE		kind) {
        return dynamic_cast<T *>(mkDataTypeFlowObj(name, kind));
    }

	virtual bool addDataTypeFlowObj(IDataTypeFlowObj *t) = 0;

    virtual IDataTypePackedStruct *findDataTypePackedStruct(
            const std::string   &name) = 0;

    virtual IDataTypePackedStruct *mkDataTypePackedStruct(
            const std::string   &name,
            Endian              endian=Endian::Little) = 0;

    virtual bool addDataTypePackedStruct(
            IDataTypePackedStruct   *type) = 0;

	virtual IModelActivityParallel *mkModelActivityParallel() = 0;

	virtual IModelActivityReplicate *mkModelActivityReplicate(
			vsc::dm::IModelExpr			*count) = 0;

	virtual IModelActivitySchedule *mkModelActivitySchedule() = 0;

	virtual IModelActivityScope *mkModelActivityScope(ModelActivityScopeT t) = 0;

	virtual IModelActivitySequence *mkModelActivitySequence() = 0;

	virtual IModelActivityTraverse *mkModelActivityTraverse(
			IModelFieldAction		*target,
			vsc::dm::IModelConstraint	*with_c,
			bool					own_with_c,
			IModelActivity			*activity,
			bool					owned) = 0;

    virtual IModelEvalIterator *mkModelEvalIterator(
            IModelActivityScope     *activity) = 0;

	virtual IModelFieldAction *mkModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type) = 0;

	virtual IModelFieldAction *mkModelFieldActionType(
			vsc::dm::ITypeField			*type) = 0;

	virtual IModelFieldClaim *mkModelFieldClaim(
			ITypeFieldClaim			*type) = 0;

	virtual IModelFieldComponent *mkModelFieldComponentRoot(
			IDataTypeComponent		*type,
			const std::string		&name,
            const vsc::dm::ValRef   &val) = 0;

	virtual IModelFieldComponent *mkModelFieldComponentType(
			vsc::dm::ITypeField			*type) = 0;

	virtual IModelFieldExecutor *mkModelFieldExecutor(
			vsc::dm::ITypeField			*type) = 0;

	virtual IModelFieldExecutorClaim *mkModelFieldExecutorClaim(
			vsc::dm::ITypeField			*type) = 0;

	virtual IModelFieldInOut *mkModelFieldInOut(
			ITypeFieldInOut			*type) = 0;

	virtual IModelFieldPool *mkModelFieldPoolType(
			vsc::dm::ITypeField			*type) = 0;

	virtual IModelFieldRegGroup *mkModelFieldRegGroup(
            vsc::dm::ITypeField         *type) = 0;

	virtual IPoolBindDirective *mkPoolBindDirective(
			PoolBindKind				kind,
			vsc::dm::ITypeExprFieldRef		*pool,
			vsc::dm::ITypeExprFieldRef		*target) = 0;

    virtual IPyImport *findPyImport(
            const std::string           &path,
            bool                        create=true) = 0;

    virtual const std::vector<IPyImportUP> &getPyImports() const = 0;

    virtual IPyImport *mkPyImport(
            const std::string           &path) = 0;

    virtual bool addPyImport(IPyImport *imp) = 0;

    virtual ITypeExecGroup *mkTypeExecGroup(
            ExecKindT               kind,
            ITypeExecGroup          *super) = 0;

    virtual ITypeExecProc *mkTypeExecProc(
            ExecKindT               kind,
            ITypeProcStmtScope      *body) = 0;

    virtual ITypeExprMethodCallContext *mkTypeExprMethodCallContext(
            IDataTypeFunction                           *target,
            vsc::dm::ITypeExpr                          *context,
            const std::vector<vsc::dm::ITypeExpr *>     &params,
            bool                                        owned=true) = 0;

    virtual ITypeExprMethodCallStatic *mkTypeExprMethodCallStatic(
            IDataTypeFunction                           *target,
            const std::vector<vsc::dm::ITypeExpr *>     &params,
            bool                                        owned=true) = 0;

    virtual ITypeExprPyImportRef *mkTypeExprPyImportRef(
            IPyImport                                   *imp) = 0;

    virtual ITypeExprPythonFieldRef *mkTypeExprPythonFieldRef(
        vsc::dm::ITypeExpr      *base,
        bool                    owned,
        const std::string       &name) = 0;

    virtual ITypeExprPythonMethodCall *mkTypeExprPythonMethodCall(
        vsc::dm::ITypeExpr                          *base,
        bool                                        owned,
        const std::vector<vsc::dm::ITypeExpr *>     &params) = 0;

    virtual ITypeExprPythonModuleRef *mkTypeExprPythonModuleRef(
        IPyImport                                   *imp) = 0;

	virtual ITypeFieldActivity *mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) = 0;

    virtual ITypeFieldAddrClaim *mkTypeFieldAddrClaim(
            const std::string           &name,
            vsc::dm::IDataType          *type,
            bool                        owned,
            vsc::dm::IDataTypeStruct    *trait_t) = 0;

    virtual ITypeFieldAddrClaimTransparent *mkTypeFieldAddrClaimTransparent(
            const std::string           &name,
            vsc::dm::IDataType          *type,
            bool                        owned,
            vsc::dm::IDataTypeStruct    *trait_t) = 0;

	virtual ITypeFieldClaim *mkTypeFieldClaim(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_lock) = 0;

	virtual ITypeFieldExecutor *mkTypeFieldExecutor(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					owned) = 0;

	virtual ITypeFieldExecutorClaim *mkTypeFieldExecutorClaim(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					owned) = 0;

	virtual ITypeFieldInOut *mkTypeFieldInOut(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_input) = 0;

	virtual ITypeFieldPool *mkTypeFieldPool(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					own,
			vsc::dm::TypeFieldAttr		attr,
			int32_t					decl_size) = 0;

    virtual ITypeFieldReg *mkTypeFieldReg(
            const std::string       &name,
            vsc::dm::IDataType      *type,
            bool                    own) = 0;

    virtual ITypeFieldRegGroup *mkTypeFieldRegGroup(
            const std::string       &name,
            vsc::dm::IDataType      *type,
            bool                    own) = 0;

    virtual ITypeFieldRegGroupArr *mkTypeFieldRegGroupArr(
            const std::string       &name,
            vsc::dm::IDataType      *type,
            bool                    own_type,
            vsc::dm::IDataType      *elem_type,
            bool                    own_elem_type,
            int32_t                 size) = 0;

	virtual ITypeProcStmtAssign *mkTypeProcStmtAssign(
			vsc::dm::ITypeExpr		*lhs,
			TypeProcStmtAssignOp	op,
			vsc::dm::ITypeExpr		*rhs) = 0;

	virtual ITypeProcStmtBreak *mkTypeProcStmtBreak() = 0;

	virtual ITypeProcStmtContinue *mkTypeProcStmtContinue() = 0;

	virtual ITypeProcStmtExpr *mkTypeProcStmtExpr(
            vsc::dm::ITypeExpr *e) = 0;

	virtual ITypeProcStmtForeach *mkTypeProcStmtForeach(
			vsc::dm::ITypeExpr		*target,
			ITypeProcStmt		*body) = 0;

	virtual ITypeProcStmtIfClause *mkTypeProcStmtIfClause(
            vsc::dm::ITypeExpr          *cond,
            ITypeProcStmt               *stmt) = 0;

	virtual ITypeProcStmtIfElse *mkTypeProcStmtIfElse(
        const std::vector<ITypeProcStmtIfClause *>      &if_c,
        ITypeProcStmt                                   *else_c) = 0;
	
	virtual ITypeProcStmtMatch *mkTypeProcStmtMatch(
			vsc::dm::ITypeExpr		*cond) = 0;

    virtual ITypeProcStmtMatchChoice *mkTypeProcStmtMatchChoice(
            vsc::dm::ITypeExprRangelist     *cond,
            ITypeProcStmt                   *body) = 0;

	virtual ITypeProcStmtRepeat *mkTypeProcStmtRepeat(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) = 0;

	virtual ITypeProcStmtRepeatWhile *mkTypeProcStmtRepeatWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) = 0;

	virtual ITypeProcStmtReturn *mkTypeProcStmtReturn(
			vsc::dm::ITypeExpr		*expr) = 0;

	virtual ITypeProcStmtScope *mkTypeProcStmtScope() = 0;

	virtual ITypeProcStmtScope *mkTypeProcStmtScope(
        const std::vector<ITypeProcStmt *> &stmts
    ) = 0;

	virtual ITypeProcStmtVarDecl *mkTypeProcStmtVarDecl(
			const std::string	 &name,
			vsc::dm::IDataType		 *type,
			bool				 own,
			vsc::dm::ITypeExpr		 *init) = 0;

	virtual ITypeProcStmtWhile *mkTypeProcStmtWhile(
			vsc::dm::ITypeExpr		*cond,
			ITypeProcStmt		*body) = 0;

	virtual ITypeProcStmtYield *mkTypeProcStmtYield() = 0;

    /**
     * @brief Creates a new Val to hold a Python object. 
     * 
     * @param obj 
     * @return ValRefPyObj 
     */
    virtual ValRefPyObj mkValPyObj(pyapi::PyEvalObj *obj) = 0;

};

}
}
}
