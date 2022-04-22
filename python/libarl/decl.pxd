
cimport libvsc.decl as vsc

ctypedef IDataTypeAction *IDataTypeActionP

cdef extern from "arl/IArl.h" namespace "arl":
    cdef cppclass IArl:
        IContext *mkContext(vsc.IContext *)
        
cdef extern IArl *py_get_arl(const char *)

cdef extern from "arl/IContext.h" namespace "arl":
    cdef cppclass IContext(vsc.IContext):
        pass
    
cdef extern from "arl/IDataTypeAction.h" namespace "arl":
    cdef cppclass IDataTypeAction(vsc.IDataTypeStruct):
        pass

    
