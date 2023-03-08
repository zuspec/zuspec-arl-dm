
cimport libvsc_dm.decl as vsc
cimport debug_mgr.decl as dm

from libcpp.string cimport string as cpp_string
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr
from libcpp cimport bool
from libc.stdint cimport int32_t
cimport cpython.ref as cpy_ref

ctypedef IContext *IContextP
ctypedef IDataTypeAction *IDataTypeActionP
ctypedef IDataTypeActivity *IDataTypeActivityP
ctypedef unique_ptr[IDataTypeActivity] IDataTypeActivityUP
ctypedef IDataTypeActivityScope *IDataTypeActivityScopeP
ctypedef IDataTypeActivityParallel *IDataTypeActivityParallelP
ctypedef IDataTypeActivityReplicate *IDataTypeActivityReplicateP
ctypedef IDataTypeActivitySchedule *IDataTypeActivityScheduleP
ctypedef IDataTypeActivitySequence *IDataTypeActivitySequenceP
ctypedef IDataTypeActivityTraverse *IDataTypeActivityTraverseP
ctypedef IDataTypeComponent *IDataTypeComponentP
ctypedef IDataTypeFlowObj *IDataTypeFlowObjP
ctypedef IDataTypeFunction *IDataTypeFunctionP
ctypedef IFactory *IFactoryP
ctypedef IModelEvalIterator *IModelEvalIteratorP
ctypedef IModelFieldAction *IModelFieldActionP
ctypedef IModelFieldComponent *IModelFieldComponentP
ctypedef IModelFieldComponentRoot *IModelFieldComponentRootP
ctypedef IModelFieldExecutor *IModelFieldExecutorP
ctypedef IModelFieldPool *IModelFieldPoolP
ctypedef IPoolBindDirective *IPoolBindDirectiveP
ctypedef unique_ptr[IPoolBindDirective] IPoolBindDirectiveUP
ctypedef ITypeFieldActivity *ITypeFieldActivityP
ctypedef unique_ptr[ITypeFieldActivity] ITypeFieldActivityUP
ctypedef ITypeFieldClaim *ITypeFieldClaimP
ctypedef ITypeFieldInOut *ITypeFieldInOutP
ctypedef ITypeFieldPool *ITypeFieldPoolP
ctypedef ITypeProcStmt *ITypeProcStmtP 
ctypedef ITypeProcStmtDeclScope *ITypeProcStmtDeclScopeP 

cdef extern from "zsp/arl/dm/IContext.h" namespace "zsp::arl::dm":
    cdef cppclass IContext(vsc.IContext):
        vsc.IModelField *buildModelAction(
            IDataTypeAction *t,
            const cpp_string &)
        IModelFieldComponent *buildModelComponent(
            IDataTypeComponent *t,
            const cpp_string &)
        IDataTypeAction *findDataTypeAction(const cpp_string &)
        IDataTypeAction *mkDataTypeAction(const cpp_string &)
        IDataTypeActivityParallel *mkDataTypeActivityParallel()
        IDataTypeActivityReplicate *mkDataTypeActivityReplicate(vsc.ITypeExpr *)
        IDataTypeActivitySchedule *mkDataTypeActivitySchedule()
        IDataTypeActivitySequence *mkDataTypeActivitySequence()
        IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
            vsc.ITypeExprFieldRef *,
            vsc.ITypeConstraint *)
        bool addDataTypeAction(IDataTypeAction *)
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
        const cpp_vector[ITypeFieldActivityP] &activities() const
        void addActivity(ITypeFieldActivity *)
        
cdef extern from "zsp/arl/dm/IDataTypeActivity.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeActivity(vsc.IDataType):
        pass
        
cdef extern from "zsp/arl/dm/IDataTypeActivityScope.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeActivityScope(IDataTypeActivity, vsc.IDataTypeStruct):
        void addActivity(ITypeFieldActivity *)
        const cpp_vector[ITypeFieldActivityP] &getActivities() const
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
    
cdef extern from "zsp/arl/dm/IDataTypeComponent.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeComponent(vsc.IDataTypeStruct):
        const cpp_vector[IDataTypeActionP] &getActionTypes() const
        void addActionType(IDataTypeAction *)
        void addPoolBindDirective(IPoolBindDirective *)
        cpp_vector[IPoolBindDirectiveUP] &getPoolBindDirectives() const
        pass
    
cdef extern from "zsp/arl/dm/IDataTypeFlowObj.h" namespace "zsp::arl::dm":
    cdef enum FlowObjKindE:
        Buffer   "zsp::arl::dm::FlowObjKindE::Buffer"
        Resource "zsp::arl::dm::FlowObjKindE::Resource"
        State    "zsp::arl::dm::FlowObjKindE::State"
        Stream   "zsp::arl::dm::FlowObjKindE::Stream"

    cdef cppclass IDataTypeFlowObj(vsc.IDataTypeStruct):
        FlowObjKindE kind() const

cdef extern from "zsp/arl/IDataTypeFunction.h" namespace "zsp::arl::dm":
    cdef cppclass IDataTypeFunction(ITypeProcStmtDeclScope):
        pass

cdef extern from "zsp/arl/dm/IFactory.h" namespace "zsp::arl::dm":
    cdef cppclass IFactory:
        void init(dm.IDebugMgr *)
        IContext *mkContext(vsc.IContext *vsc_ctxt)

cdef extern from "zsp/arl/dm/IModelBuildContext.h" namespace "zsp::arl::dm":
    cdef cppclass IModelBuildContext:
        IContext *ctxt()
        pass

# TODO:
# cdef extern from "zsp/arl/dm/IModelEvaluator.h" namespace "zsp::arl::dm":
#     cdef cppclass IModelEvaluator:
#         IModelEvalIterator *eval(
#             vsc.IRandState *,
#             IModelFieldComponent *, 
#             IDataTypeAction *)

# cdef extern from "zsp/arl/dm/IModelEvalIterator.h" namespace "zsp::arl::dm":
#     cdef enum ModelEvalNodeT:
#         Action   "zsp::arl::dm::ModelEvalNodeT::Action"
#         Parallel "zsp::arl::dm::ModelEvalNodeT::Parallel"
#         Sequence "zsp::arl::dm::ModelEvalNodeT::Sequence"
#     cdef cppclass IModelEvalIterator:
#         bool next()
#         ModelEvalNodeT type() const
#         IModelFieldAction *action()
#        IModelEvalIterator *iterator()

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

cdef extern from "zsp/arl/dm/IVisitor.h" namespace "zsp::arl::dm":
    cdef cppclass IVisitor(vsc.IVisitor):
        pass
    
cdef extern from "VisitorProxy.h" namespace "zsp::arl::dm":
    cdef cppclass VisitorProxy(IVisitor):
        VisitorProxy(cpy_ref.PyObject *)

cdef extern IModelBuildContext *mkModelBuildContextArl(IContext *ctxt)

