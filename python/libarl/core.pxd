
from libarl cimport decl
from libcpp cimport bool
cimport libvsc.core as vsc

cdef class Arl(object):
    cdef vsc.Vsc            _vsc
    cdef decl.IArl          *_hndl
    
    cpdef Context mkContext(self)

cdef class Context(vsc.Context):

    @staticmethod
    cdef mk(decl.IContext *ctxt, bool owned=*)


cdef class DataTypeAction(vsc.DataTypeStruct):

    cdef decl.IDataTypeAction *asAction(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeAction *, bool owned=*)
    
