
from libarl cimport decl
from libcpp cimport bool
cimport libvsc.core as vsc

cdef class Arl(object):
    cdef vsc.Vsc            _vsc
    cdef decl.IArl          *_hndl
    
    cpdef Context mkContext(self)

cdef class Context(vsc.Context):

    cpdef DataTypeComponent findDataTypeComponent(self, name)
    cpdef DataTypeComponent mkDataTypeComponent(self, name)
    cpdef bool addDataTypeComponent(self, DataTypeComponent comp_t)
    
    cdef decl.IContext *asContext(self)
    
    @staticmethod
    cdef mk(decl.IContext *ctxt, bool owned=*)
    
cdef class DataTypeStruct(vsc.DataTypeStruct):
    pass

cdef class DataTypeAction(DataTypeStruct):

    cdef decl.IDataTypeAction *asAction(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeAction *, bool owned=*)
    
cdef class DataTypeComponent(DataTypeStruct):

    cdef decl.IDataTypeComponent *asComponent(self)
    
    @staticmethod
    cdef DataTypeComponent mk(decl.IDataTypeComponent *, bool owned=*)
    
