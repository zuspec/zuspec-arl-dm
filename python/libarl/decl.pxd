
cimport libvsc.decl as vsc

from libcpp.string cimport string as cpp_string
from libcpp cimport bool

ctypedef IContext *IContextP
ctypedef IDataTypeAction *IDataTypeActionP
ctypedef IDataTypeComponent *IDataTypeComponentP

cdef extern from "arl/IArl.h" namespace "arl":
    cdef cppclass IArl:
        IContext *mkContext(vsc.IContext *)
        
        
cdef extern IArl *py_get_arl(const char *)

cdef extern from "arl/IContext.h" namespace "arl":
    cdef cppclass IContext(vsc.IContext):
        vsc.IModelField *buildModelComponent(IDataTypeComponent *t)
        IDataTypeAction *findDataTypeAction(const cpp_string &)
        IDataTypeAction *mkDataTypeAction(const cpp_string &)
        bool addDataTypeAction(IDataTypeAction *)
        IDataTypeComponent *findDataTypeComponent(const cpp_string &)
        IDataTypeComponent *mkDataTypeComponent(const cpp_string &)
        bool addDataTypeComponent(IDataTypeComponent *)
        
cdef extern from "arl/IDataTypeAction.h" namespace "arl":
    cdef cppclass IDataTypeAction(vsc.IDataTypeStruct):
        pass
    
cdef extern from "arl/IDataTypeComponent.h" namespace "arl":
    cdef cppclass IDataTypeComponent(vsc.IDataTypeStruct):
        pass
    
cdef extern from "arl/IDataTypeFlowObj.h" namespace "arl":
    cdef cppclass IDataTypeFlowObj(vsc.IDataTypeStruct):
        pass

    
