
from libarl cimport decl
from libcpp cimport bool
cimport libvsc.core as vsc

cdef class Arl(object):
    cdef vsc.Vsc            _vsc
    cdef decl.IArl          *_hndl
    
    cpdef Context mkContext(self)

cdef class Context(vsc.Context):

    cpdef vsc.ModelField buildModelAction(self, DataTypeAction t, name)
    cpdef vsc.ModelField buildModelComponent(self, DataTypeComponent t, name)
    cpdef DataTypeAction findDataTypeAction(self, name)
    cpdef DataTypeAction mkDataTypeAction(self, name)
    cpdef bool addDataTypeAction(self, DataTypeAction)
    cpdef DataTypeComponent findDataTypeComponent(self, name)
    cpdef DataTypeComponent mkDataTypeComponent(self, name)
    cpdef bool addDataTypeComponent(self, DataTypeComponent comp_t)
    
    cdef decl.IContext *asContext(self)
    
    @staticmethod
    cdef mk(decl.IContext *ctxt, bool owned=*)
    
cdef class DataTypeAction(vsc.DataTypeStruct):

    cdef decl.IDataTypeAction *asAction(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeAction *, bool owned=*)
    
cdef class DataTypeComponent(vsc.DataTypeStruct):

    cdef decl.IDataTypeComponent *asComponent(self)
    
    @staticmethod
    cdef DataTypeComponent mk(decl.IDataTypeComponent *, bool owned=*)
    
