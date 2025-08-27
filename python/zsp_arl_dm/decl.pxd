cimport vsc_dm.decl as vsc
cimport debug_mgr.decl as dm

from libcpp.string cimport string as cpp_string
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr
from libcpp cimport bool
from libc.stdint cimport int32_t
from libc.stdint cimport int64_t
from libc.stdint cimport uint64_t
from libc.stdint cimport uint32_t
cimport cpython.ref as cpy_ref

ctypedef IContext *IContextP
ctypedef IDataTypeAction *IDataTypeActionP
ctypedef IDataTypeActivity *IDataTypeActivityP
ctypedef vsc.UP[IDataTypeActivity] IDataTypeActivityUP
ctypedef IDataTypeActivityScope *IDataTypeActivityScopeP
ctypedef IDataTypeActivityParallel *IDataTypeActivityParallelP
ctypedef IDataTypeActivityReplicate *IDataTypeActivityReplicateP
ctypedef IDataTypeActivitySchedule *IDataTypeActivityScheduleP
ctypedef IDataTypeActivitySequence *IDataTypeActivitySequenceP
ctypedef IDataTypeActivityTraverse *IDataTypeActivityTraverseP
ctypedef IDataTypeAddrClaim *IDataTypeAddrClaimP
ctypedef IDataTypeAddrClaimTransparent *IDataTypeAddrClaimTransparentP
ctypedef IDataTypeAddrHandle *IDataTypeAddrHandleP
ctypedef IDataTypeArlStruct *IDataTypeArlStructP
ctypedef IDataTypeComponent *IDataTypeComponentP
ctypedef IDataTypeFlowObj *IDataTypeFlowObjP
ctypedef IDataTypeFunction *IDataTypeFunctionP
ctypedef vsc.UP[IDataTypeFunction] IDataTypeFunctionUP
ctypedef IDataTypeFunctionParamDecl *IDataTypeFunctionParamDeclP
ctypedef IDataTypePackedStruct *IDataTypePackedStructP
ctypedef IDataTypeReg *IDataTypeRegP
ctypedef IDataTypeResource *IDataTypeResourceP
ctypedef IDataTypeTransparentAddrSpace *IDataTypeTransparentAddrSpaceP
ctypedef IDataTypePureComponent *IDataTypePureComponentP
ctypedef IDataTypePyObj *IDataTypePyObjP
ctypedef IDataTypeCoreLibComponent *IDataTypeCoreLibComponentP
ctypedef IFactory *IFactoryP
ctypedef IModelEvalIterator *IModelEvalIteratorP
ctypedef IModelFieldAction *IModelFieldActionP
ctypedef IModelFieldComponent *IModelFieldComponentP
ctypedef IModelFieldComponentRoot *IModelFieldComponentRootP
ctypedef IModelFieldExecutor *IModelFieldExecutorP
ctypedef IModelFieldPool *IModelFieldPoolP
ctypedef IPoolBindDirective *IPoolBindDirectiveP
ctypedef vsc.UP[IPoolBindDirective] IPoolBindDirectiveUP
ctypedef ITypeExec *ITypeExecP
ctypedef vsc.UP[ITypeExec] ITypeExecUP
ctypedef ITypeExecProc *ITypeExecProcP
ctypedef vsc.UP[ITypeExecProc] ITypeExecProcUP
ctypedef ITypeFieldActivity *ITypeFieldActivityP
ctypedef vsc.UP[ITypeFieldActivity] ITypeFieldActivityUP
ctypedef ITypeFieldClaim *ITypeFieldClaimP
ctypedef ITypeFieldInOut *ITypeFieldInOutP
ctypedef ITypeFieldPool *ITypeFieldPoolP
ctypedef ITypeFieldReg *ITypeFieldRegP
ctypedef ITypeProcStmt *ITypeProcStmtP 
ctypedef vsc.UP[ITypeProcStmt] ITypeProcStmtUP 
ctypedef ITypeProcStmtDeclScope *ITypeProcStmtDeclScopeP 
ctypedef ITypeProcStmtVarDecl *ITypeProcStmtVarDeclP
ctypedef ITypeProcStmtAssign *ITypeProcStmtAssignP
ctypedef ITypeProcStmtBreak *ITypeProcStmtBreakP
ctypedef ITypeProcStmtContinue *ITypeProcStmtContinueP
ctypedef ITypeProcStmtExpr *ITypeProcStmtExprP
ctypedef ITypeProcStmtForeach *ITypeProcStmtForeachP
ctypedef ITypeProcStmtIfClause *ITypeProcStmtIfClauseP
ctypedef vsc.UP[ITypeProcStmtIfClause] ITypeProcStmtIfClauseUP
ctypedef ITypeProcStmtIfElse *ITypeProcStmtIfElseP
ctypedef ITypeProcStmtMatch *ITypeProcStmtMatchP
ctypedef ITypeProcStmtMatchChoice *ITypeProcStmtMatchChoiceP
ctypedef vsc.UP[ITypeProcStmtMatchChoice] ITypeProcStmtMatchChoiceUP
ctypedef ITypeProcStmtRepeat *ITypeProcStmtRepeatP
ctypedef ITypeProcStmtRepeatWhile *ITypeProcStmtRepeatWhileP
ctypedef ITypeProcStmtReturn *ITypeProcStmtReturnP
ctypedef ITypeProcStmtScope *ITypeProcStmtScopeP
ctypedef vsc.UP[ITypeProcStmtScope] ITypeProcStmtScopeUP
ctypedef ITypeProcStmtYield *ITypeProcStmtYieldP

cdef extern from "zsp/arl/dm/IContext.h" namespace "zsp::arl::dm":
    cdef cppclass IContext(vsc.IContext):
        IDataTypeAction *findDataTypeAction(const cpp_string &)
        IDataTypeFunction *findDataTypeFunction(const cpp_string &)
        IDataTypeAction *mkDataTypeAction(const cpp_string &)
        const cpp_vector[IDataTypeFunctionP] &getDataTypeFunctions() const
        IDataTypeActivityParallel *mkDataTypeActivityParallel()
        IDataTypeActivityReplicate *mkDataTypeActivityReplicate(vsc.ITypeExpr *)
        IDataTypeActivitySchedule *mkDataTypeActivitySchedule()
        IDataTypeActivitySequence *mkDataTypeActivitySequence()
        IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
            vsc.ITypeExprFieldRef *,
            vsc.ITypeConstraint *)
        bool addDataTypeAction(IDataTypeAction *)
#        IDataTypeArlStructP mkDataTypeArlStruct(const cpp_string &)
        IDataTypeAddrClaimP mkDataTypeAddrClaim(const cpp_string &)
        IDataTypeAddrClaimTransparentP mkDataTypeAddrClaimTransparent(const cpp_string &)
        IDataTypeComponent *findDataTypeComponent(const cpp_string &)
        IDataTypeComponent *mkDataTypeComponent(const cpp_string &)
        bool addDataTypeComponent(IDataTypeComponent *)
        IDataTypeFlowObj *findDataTypeFlowObj(const cpp_string &name, FlowObjKindE kind)
        IDataTypeFlowObj *mkDataTypeFlowObj(const cpp_string &name, FlowObjKindE kind)
        bool addDataTypeFlowObj(IDataTypeFlowObj *)

#TODO:        IModelEvaluator *mkModelEvaluator()

        IPoolBindDirective *mkPoolBindDirective(
            PoolBindKind                kind,
            vsc.ITypeExprFieldRef       *pool,
            vsc.ITypeExprFieldRef       *target)
        ITypeFieldActivity *mkTypeFieldActivity(const cpp_string &, IDataTypeActivity *, bool)
        ITypeExecProc *mkTypeExecProc(ExecKindT kind, ITypeProcStmtScope *body)
        ITypeFieldClaim *mkTypeFieldClaim(const cpp_string &, vsc.IDataType *, bool)
        ITypeFieldInOut *mkTypeFieldInOut(const cpp_string &, vsc.IDataType *, bool)
        ITypeFieldPool *mkTypeFieldPool(
            const cpp_string &, 
            vsc.IDataType *, 
            bool own,
            vsc.TypeFieldAttr, 
            int32_t)
        
cdef extern from "zsp/arl/dm/IDataTypeAction.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeAction(vsc.IDataTypeStruct):
        IDataTypeComponent *getComponentType()
        void setComponentType(IDataTypeComponent *)
        vsc.ITypeFieldRef *getCompField() const
        const cpp_vector[ITypeFieldActivityUP] &activities() const
        void addActivity(ITypeFieldActivity *)
        
cdef extern from "zsp/arl/dm/IDataTypeActivity.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeActivity(vsc.IDataType):
        pass
        
cdef extern from "zsp/arl/dm/IDataTypeActivityScope.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeActivityScope(IDataTypeActivity, vsc.IDataTypeStruct):
        void addActivity(ITypeFieldActivity *)
        const cpp_vector[ITypeFieldActivityUP] &getActivities() const
        # const cpp_string &name() const
        # void addField(vsc.ITypeField *)
        # vsc.ITypeField *getField(int32_t idx)
        # const cpp_vector[unique_ptr[vsc.ITypeField]] &getFields() const
        # void addConstraint(vsc.ITypeConstraint *)
        # const cpp_vector[unique_ptr[vsc.ITypeConstraint]] &getConstraints() const
        
        pass

cdef extern from "zsp/arl/dm/IDataTypeActivityReplicate.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeActivityReplicate(IDataTypeActivityScope):
        vsc.ITypeExpr *getCount() const

cdef extern from "zsp/arl/dm/IDataTypeActivityParallel.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeActivityParallel(IDataTypeActivityScope):
        pass
        
cdef extern from "zsp/arl/dm/IDataTypeActivitySchedule.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeActivitySchedule(IDataTypeActivityScope):
        pass
    
cdef extern from "zsp/arl/dm/IDataTypeActivitySequence.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeActivitySequence(IDataTypeActivityScope):
        pass
    
cdef extern from "zsp/arl/dm/IDataTypeActivityTraverse.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeActivityTraverse(IDataTypeActivity):
        vsc.ITypeExprFieldRef *getTarget() const
        vsc.ITypeConstraint *getWithC() const
        void setWithC(vsc.ITypeConstraint *c)

cdef extern from "zsp/arl/dm/IDataTypeArlStruct.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeArlStruct(vsc.IDataTypeStruct):
        const cpp_vector[ITypeExecUP] &getExecs(ExecKindT kind) const
        void addExec(ITypeExec *exec)
        void addFunction(IDataTypeFunction *f, bool owned)
        const cpp_vector[IDataTypeFunctionUP] &getFunctions()

cdef extern from "zsp/arl/dm/IDataTypeAddrClaim.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeAddrClaim(IDataTypeArlStruct):
        pass

cdef extern from "zsp/arl/dm/IDataTypeAddrClaimTransparent.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeAddrClaimTransparent(IDataTypeAddrClaim):
        pass

cdef extern from "zsp/arl/dm/IDataTypeAddrHandle.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeAddrHandle(vsc.IDataTypeStruct):
        pass
    
cdef extern from "zsp/arl/dm/IDataTypeComponent.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeComponent(vsc.IDataTypeStruct):
        const cpp_vector[IDataTypeActionP] &getActionTypes() const
        void addActionType(IDataTypeAction *)
        void addPoolBindDirective(IPoolBindDirective *)
        cpp_vector[IPoolBindDirectiveUP] &getPoolBindDirectives() const
        pass

cdef extern from "zsp/arl/dm/IDataTypePureComponent.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypePureComponent(IDataTypeComponent):
        pass

cdef extern from "zsp/arl/dm/RegAccess.h" namespace "zsp::arl::dm":
    cdef enum RegAccess:
        RegAccess_NoAccess "zsp::arl::dm::RegAccess::NoAccess"
        RegAccess_RW "zsp::arl::dm::RegAccess::RW"
        RegAccess_RO "zsp::arl::dm::RegAccess::RO"
        RegAccess_WO "zsp::arl::dm::RegAccess::WO"
        RegAccess_W1 "zsp::arl::dm::RegAccess::W1"
        RegAccess_CLR "zsp::arl::dm::RegAccess::CLR"
        RegAccess_SET "zsp::arl::dm::RegAccess::SET"


    cdef cppclass IDataTypeReg(IDataTypePureComponent):
        IDataTypePackedStruct *getDataType() const
        uint32_t getOffset() const
        uint32_t getWidth() const
        RegAccess getAccess() const

cdef extern from "zsp/arl/dm/IDataTypePyObj.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypePyObj(vsc.IDataType):
        pass

cdef extern from "zsp/arl/dm/IDataTypeResource.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeResource(vsc.IDataType):
        pass

cdef extern from "zsp/arl/dm/IDataTypeTransparentAddrSpace.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeTransparentAddrSpace(vsc.IDataType):
        pass

cdef extern from "vsc/dm/IValOpsDelegator.h" namespace "vsc::dm":
    cdef cppclass IValOpsDelegator:
        pass

cdef extern from "zsp/arl/dm/IDataTypeCoreLibComponent.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeCoreLibComponent(IDataTypeComponent, IValOpsDelegator):
        pass
    
cdef extern from "zsp/arl/dm/IDataTypeFlowObj.h" namespace "zsp::arl::dm":
    cdef enum FlowObjKindE:
        Buffer   "zsp::arl::dm::FlowObjKindE::Buffer"
        Resource "zsp::arl::dm::FlowObjKindE::Resource"
        State    "zsp::arl::dm::FlowObjKindE::State"
        Stream   "zsp::arl::dm::FlowObjKindE::Stream"

    cdef cppclass IDataTypeFlowObj(vsc.IDataTypeStruct):
        FlowObjKindE kind() const

cdef extern from "zsp/arl/dm/ITypeProcStmt.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmt(vsc.IAccept):
        pass

cdef extern from "zsp/arl/dm/ITypeProcStmtAssign.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtAssign(ITypeProcStmt):
        vsc.ITypeExpr *getLhs() const
        vsc.ITypeExpr *getRhs() const

cdef extern from "zsp/arl/dm/ITypeProcStmtBreak.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtBreak(ITypeProcStmt):
        pass

cdef extern from "zsp/arl/dm/ITypeProcStmtContinue.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtContinue(ITypeProcStmt):
        pass

cdef extern from "zsp/arl/dm/ITypeProcStmtExpr.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtExpr(ITypeProcStmt):
        vsc.ITypeExpr *getExpr() const

cdef extern from "zsp/arl/dm/ITypeProcStmtForeach.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtForeach(ITypeProcStmt):
        pass

cdef extern from "zsp/arl/dm/ITypeProcStmtIfClause.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtIfClause(ITypeProcStmt):
        vsc.ITypeExpr *getCond() const
        ITypeProcStmt *getStmt() const

cdef extern from "zsp/arl/dm/ITypeProcStmtIfElse.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtIfElse(ITypeProcStmt):
        const cpp_vector[ITypeProcStmtIfClauseUP] &getIfClauses() const
        ITypeProcStmt *getElseClause() const

cdef extern from "zsp/arl/dm/ITypeProcStmtMatchChoice.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtMatchChoice(ITypeProcStmt):
        vsc.ITypeExpr *getCond() const
        ITypeProcStmt *getBody() const

cdef extern from "zsp/arl/dm/ITypeProcStmtMatch.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtMatch(ITypeProcStmt):
        vsc.ITypeExpr *getCond() const
        const cpp_vector[ITypeProcStmtMatchChoiceUP] &getChoices() const

cdef extern from "zsp/arl/dm/ITypeProcStmtRepeat.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtRepeat(ITypeProcStmt):
        vsc.ITypeExpr *getExpr() const
        ITypeProcStmt *getBody() const

cdef extern from "zsp/arl/dm/ITypeProcStmtRepeatWhile.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtRepeatWhile(ITypeProcStmt):
        vsc.ITypeExpr *getExpr() const
        ITypeProcStmt *getBody() const

cdef extern from "zsp/arl/dm/ITypeProcStmtReturn.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtReturn(ITypeProcStmt):
        vsc.ITypeExpr *getExpr() const

cdef extern from "zsp/arl/dm/ITypeProcStmtScope.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtScope(ITypeProcStmt):
        void addStatement(ITypeProcStmt *stmt, bool owned)
        const cpp_vector[ITypeProcStmtUP] &getStatements() const

cdef extern from "zsp/arl/dm/ITypeProcStmtYield.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtYield(ITypeProcStmt):
        pass
cdef extern from "zsp/arl/dm/ITypeProcStmtDeclScope.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtDeclScope(vsc.IAccept):
        vsc.IAssociatedData *getAssociatedData()
        void setAssociatedData(vsc.IAssociatedData *)
        pass

cdef extern from "zsp/arl/dm/ITypeProcStmtVarDecl.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeProcStmtVarDecl(ITypeProcStmt):
        const cpp_string &name() const
        vsc.IDataType *getDataType() const
        vsc.ITypeExpr *getInit() const

cdef extern from "zsp/arl/dm/IDataTypeFunctionParamDecl.h" namespace "zsp::arl::dm":
    cdef enum ParamDir:
        In    "zsp::arl::dm::ParamDir::In"
        Out   "zsp::arl::dm::ParamDir::Out"
        InOut "zsp::arl::dm::ParamDir::InOut"

    cdef cppclass IDataTypeFunctionParamDecl(ITypeProcStmtVarDecl):
        ParamDir getDirection() const

cdef extern from "zsp/arl/dm/IDataTypeFunction.h" namespace "zsp::arl::dm":
    cdef enum DataTypeFunctionFlags:
        NoFlags "zsp::arl::dm::DataTypeFunctionFlags::NoFlags"
        Solve "zsp::arl::dm::DataTypeFunctionFlags::Solve"
        Target "zsp::arl::dm::DataTypeFunctionFlags::Target"
        Core "zsp::arl::dm::DataTypeFunctionFlags::Core"

    cdef cppclass IDataTypeFunction(ITypeProcStmtDeclScope):
        const cpp_string &name()
        vsc.IDataType *getReturnType() const
        const cpp_vector[IDataTypeFunctionParamDeclP] &getParameters() const
        ITypeProcStmtScope *getBody() const
        DataTypeFunctionFlags getFlags() const
        bool hasFlags(DataTypeFunctionFlags) const

cdef extern from "zsp/arl/dm/IDataTypePackedStruct.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypePackedStruct(vsc.IDataTypeStruct):
        pass

cdef extern from "zsp/arl/dm/IFactory.h" namespace "zsp::arl::dm":
    cdef cppclass IFactory:
        void init(dm.IDebugMgr *)
        IContext *mkContext(vsc.IContext *vsc_ctxt)

cdef extern from "zsp/arl/dm/IModelBuildContext.h" namespace "zsp::arl::dm":
    cdef cppclass IModelBuildContext:
        IContext *ctxt()
        pass

#cdef extern from "zsp/arl/dm/IModelEvaluator.h" namespace "zsp::arl::dm":
#    cdef cppclass IModelEvaluator:
#        IModelEvalIterator *eval(
#            vsc.IRandState *,
#            IModelFieldComponent *, 
#            IDataTypeAction *)

cdef extern from "zsp/arl/dm/IModelEvalIterator.h" namespace "zsp::arl::dm":
    cdef enum ModelEvalNodeT:
        Action   "zsp::arl::dm::ModelEvalNodeT::Action"
        Parallel "zsp::arl::dm::ModelEvalNodeT::Parallel"
        Sequence "zsp::arl::dm::ModelEvalNodeT::Sequence"
    cdef cppclass IModelEvalIterator:
        bool next()
        ModelEvalNodeT type() const
        IModelFieldAction *action()
        IModelEvalIterator *iterator()

cdef extern from "zsp/arl/dm/IModelEvalIterator.h" namespace "zsp::arl::dm":
    cdef cppclass IModelEvalIterator:
        pass

cdef extern from "zsp/arl/dm/IModelFieldAction.h" namespace "zsp::arl::dm":
    cdef cppclass IModelFieldAction(vsc.IModelField):
        bool isCompound() const
        pass
        
cdef extern from "zsp/arl/dm/IModelFieldComponent.h" namespace "zsp::arl::dm":
    cdef cppclass IModelFieldComponent(vsc.IModelField):
        pass

cdef extern from "zsp/arl/dm/IModelFieldComponentRoot.h" namespace "zsp::arl::dm":
    cdef cppclass IModelFieldComponentRoot(IModelFieldComponent):
        void initCompTree()

cdef extern from "zsp/arl/dm/IModelFieldExecutor.h" namespace "zsp::arl::dm":
    cdef cppclass IModelFieldExecutor(vsc.IModelField):
        pass

cdef extern from "zsp/arl/dm/IModelFieldPool.h" namespace "zsp::arl::dm":
    cdef cppclass IModelFieldPool(vsc.IModelField):
        pass

cdef extern from "zsp/arl/dm/IPoolBindDirective.h" namespace "zsp::arl::dm":
    cdef enum PoolBindKind:
        All "zsp::arl::dm::PoolBindKind::All"
        Ref "zsp::arl::dm::PoolBindKind::Ref"

    cdef cppclass IPoolBindDirective:
        PoolBindKind kind() const
        vsc.ITypeExprFieldRef *getPool() const
        vsc.ITypeExprFieldRef *getTarget() const

cdef extern from "zsp/arl/dm/ITypeExec.h" namespace "zsp::arl::dm":
    cdef enum ExecKindT:
        ExecBody "zsp::arl::dm::ExecKindT::Body"
        ExecPreSolve "zsp::arl::dm::ExecKindT::PreSolve"
        ExecPostSolve "zsp::arl::dm::ExecKindT::PostSolve"

    cdef cppclass ITypeExec(vsc.IAccept):
        ExecKindT getKind() const

cdef extern from "zsp/arl/dm/ITypeExecProc.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeExecProc(ITypeExec):
        ITypeProcStmtScope *getBody() const
    
cdef extern from "zsp/arl/dm/ITypeFieldActivity.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeFieldActivity(vsc.ITypeField):
        pass
    
cdef extern from "zsp/arl/dm/ITypeFieldClaim.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeFieldClaim(vsc.ITypeField):
        bool isLock() const
        
cdef extern from "zsp/arl/dm/ITypeFieldInOut.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeFieldInOut(vsc.ITypeField):
        bool isInput() const
        
cdef extern from "zsp/arl/dm/ITypeFieldPool.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeFieldPool(vsc.ITypeField):
        int32_t getDeclSize()

cdef extern from "zsp/arl/dm/ITypeFieldReg.h" namespace "zsp::arl::dm":
    cdef cppclass ITypeFieldReg(vsc.ITypeField):
        int64_t getAddrOffset()
        void setAddrOffset(int64_t off)
        int32_t getWidth() const

cdef extern from "zsp/arl/dm/IVisitor.h" namespace "zsp::arl::dm":
    cdef cppclass IVisitor(vsc.IVisitor):
        pass
    
cdef extern from "VisitorProxy.h" namespace "zsp::arl::dm":
    cdef cppclass VisitorProxy(IVisitor):
        VisitorProxy(cpy_ref.PyObject *)

cdef extern IModelBuildContext *mkModelBuildContextArl(IContext *ctxt)
