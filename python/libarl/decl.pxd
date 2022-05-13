
cimport libvsc.decl as vsc

from libcpp.string cimport string as cpp_string
from libcpp cimport bool
from libc.stdint cimport int32_t

ctypedef IContext *IContextP
ctypedef IDataTypeAction *IDataTypeActionP
ctypedef IDataTypeComponent *IDataTypeComponentP
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
        vsc.IModelField *buildModelComponent(
            IDataTypeComponent *t,
            const cpp_string &)
        IDataTypeAction *findDataTypeAction(const cpp_string &)
        IDataTypeAction *mkDataTypeAction(const cpp_string &)
        bool addDataTypeAction(IDataTypeAction *)
        IDataTypeComponent *findDataTypeComponent(const cpp_string &)
        IDataTypeComponent *mkDataTypeComponent(const cpp_string &)
        bool addDataTypeComponent(IDataTypeComponent *)
        IModelEvaluator *mkModelEvaluator()
        ITypeFieldPool *mkTypeFieldPool(const cpp_string &, vsc.IDataType *, vsc.TypeFieldAttr, int32_t)
        
cdef extern from "arl/IDataTypeAction.h" namespace "arl":
    cdef cppclass IDataTypeAction(vsc.IDataTypeStruct):
        pass
    
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

cdef extern from "arl/ITypeFieldPool.h" namespace "arl":
    cdef cppclass ITypeFieldPool(vsc.ITypeField):
        int32_t getDeclSize()
    
    