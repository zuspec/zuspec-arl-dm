
cimport libvsc.decl as vsc

from libcpp.string cimport string as cpp_string
from libcpp.vector cimport vector as cpp_vector
from libcpp.memory cimport unique_ptr
from libcpp cimport bool
from libc.stdint cimport int32_t

ctypedef IContext *IContextP
ctypedef IDataTypeAction *IDataTypeActionP
ctypedef IDataTypeActivity *IDataTypeActivityP
ctypedef unique_ptr[IDataTypeActivity] IDataTypeActivityUP
ctypedef IDataTypeActivityScope *IDataTypeActivityScopeP
ctypedef IDataTypeActivitySchedule *IDataTypeActivityScheduleP
ctypedef IDataTypeActivitySequence *IDataTypeActivitySequenceP
ctypedef IDataTypeActivityTraverse *IDataTypeActivityTraverseP
ctypedef IDataTypeComponent *IDataTypeComponentP
ctypedef IModelFieldRootComponent *IModelFieldRootComponentP
ctypedef ITypeFieldActivity *ITypeFieldActivityP
ctypedef unique_ptr[ITypeFieldActivity] ITypeFieldActivityUP
ctypedef ITypeFieldClaim *ITypeFieldClaimP
ctypedef ITypeFieldInOut *ITypeFieldInOutP
ctypedef ITypeFieldPool *ITypeFieldPoolP

cdef extern from "arl/IArl.h" namespace "arl":
    cdef cppclass IArl:
        IContext *mkContext(vsc.IContext *)
        
        
cdef extern IArl *py_get_arl(const char *)

cdef extern from "arl/IContext.h" namespace "arl":
    cdef cppclass IContext(vsc.IContext):
        vsc.IModelField *buildModelAction(
            IDataTypeAction *t,
            const cpp_string &)
        IModelFieldRootComponent *buildModelComponent(
            IDataTypeComponent *t,
            const cpp_string &)
        IDataTypeAction *findDataTypeAction(const cpp_string &)
        IDataTypeAction *mkDataTypeAction(const cpp_string &)
        IDataTypeActivitySchedule *mkDataTypeActivitySchedule()
        IDataTypeActivitySequence *mkDataTypeActivitySequence()
        IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
            vsc.ITypeExprFieldRef *,
            vsc.ITypeConstraint *)
        bool addDataTypeAction(IDataTypeAction *)
        IDataTypeComponent *findDataTypeComponent(const cpp_string &)
        IDataTypeComponent *mkDataTypeComponent(const cpp_string &)
        bool addDataTypeComponent(IDataTypeComponent *)
        IModelEvaluator *mkModelEvaluator()
        ITypeFieldActivity *mkTypeFieldActivity(const cpp_string &, IDataTypeActivity *, bool)
        ITypeFieldClaim *mkTypeFieldClaim(const cpp_string &, vsc.IDataType *, bool)
        ITypeFieldInOut *mkTypeFieldInOut(const cpp_string &, vsc.IDataType *, bool)
        ITypeFieldPool *mkTypeFieldPool(const cpp_string &, vsc.IDataType *, vsc.TypeFieldAttr, int32_t)
        
cdef extern from "arl/IDataTypeAction.h" namespace "arl":
    cdef cppclass IDataTypeAction(vsc.IDataTypeStruct):
        IDataTypeComponent *getComponentType()
        void setComponentType(IDataTypeComponent *)
        const cpp_vector[ITypeFieldActivityP] &activities() const
        void addActivity(ITypeFieldActivity *)
        
cdef extern from "arl/IDataTypeActivity.h" namespace "arl":
    cdef cppclass IDataTypeActivity:
        pass
        
cdef extern from "arl/IDataTypeActivityScope.h" namespace "arl":
    cdef cppclass IDataTypeActivityScope(IDataTypeActivity, vsc.IDataTypeStruct):
        void addActivity(ITypeFieldActivity *)
        const cpp_vector[ITypeFieldActivityUP] &activities() const
        # const cpp_string &name() const
        # void addField(vsc.ITypeField *)
        # vsc.ITypeField *getField(int32_t idx)
        # const cpp_vector[unique_ptr[vsc.ITypeField]] &getFields() const
        # void addConstraint(vsc.ITypeConstraint *)
        # const cpp_vector[unique_ptr[vsc.ITypeConstraint]] &getConstraints() const
        
        pass
        
cdef extern from "arl/IDataTypeActivitySchedule.h" namespace "arl":
    cdef cppclass IDataTypeActivitySchedule(IDataTypeActivityScope):
        pass
    
cdef extern from "arl/IDataTypeActivitySequence.h" namespace "arl":
    cdef cppclass IDataTypeActivitySequence(IDataTypeActivityScope):
        pass
    
cdef extern from "arl/IDataTypeActivityTraverse.h" namespace "arl":
    cdef cppclass IDataTypeActivityTraverse(IDataTypeActivity):
        vsc.ITypeExprFieldRef *getTarget() const
        vsc.ITypeConstraint *getWithC() const
        void setWithC(vsc.ITypeConstraint *c)
    
cdef extern from "arl/IDataTypeComponent.h" namespace "arl":
    cdef cppclass IDataTypeComponent(vsc.IDataTypeStruct):
        pass
    
cdef extern from "arl/IDataTypeFlowObj.h" namespace "arl":
    cdef cppclass IDataTypeFlowObj(vsc.IDataTypeStruct):
        pass
    
cdef extern from "arl/IModelEvaluator.h" namespace "arl":
    cdef cppclass IModelEvaluator:
        IModelEvalIterator *eval(vsc.IModelField *, IDataTypeAction *)

cdef extern from "arl/IModelEvalIterator.h" namespace "arl":
    cdef enum ModelEvalNodeT:
        Action   "arl::ModelEvalNodeT::Action"
        Parallel "arl::ModelEvalNodeT::Parallel"
        Sequence "arl::ModelEvalNodeT::Sequence"
    cdef cppclass IModelEvalIterator:
        bool next()
        ModelEvalNodeT type() const
        vsc.IModelField *action()
        IModelEvalIterator *iterator()
        
cdef extern from "arl/IModelFieldRootComponent.h" namespace "arl":
    cdef cppclass IModelFieldRootComponent(vsc.IModelField):
        pass
    
cdef extern from "arl/ITypeFieldActivity.h" namespace "arl":
    cdef cppclass ITypeFieldActivity(vsc.ITypeField):
        pass
    
cdef extern from "arl/ITypeFieldClaim.h" namespace "arl":
    cdef cppclass ITypeFieldClaim(vsc.ITypeField):
        bool isLock() const
        
cdef extern from "arl/ITypeFieldInOut.h" namespace "arl":
    cdef cppclass ITypeFieldInOut(vsc.ITypeField):
        bool isInput() const
        
cdef extern from "arl/ITypeFieldPool.h" namespace "arl":
    cdef cppclass ITypeFieldPool(vsc.ITypeField):
        int32_t getDeclSize()
    
    