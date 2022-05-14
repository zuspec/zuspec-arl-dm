
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
    
    cpdef ModelEvaluator mkModelEvaluator(self)
    cpdef TypeFieldClaim mkTypeFieldClaim(self, name, vsc.DataType, bool)
    cpdef TypeFieldInOut mkTypeFieldInOut(self, name, vsc.DataType, bool)
    cpdef TypeFieldPool mkTypeFieldPool(self, name, vsc.DataType, vsc.TypeFieldAttr, decl_size)
    
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

cdef class ModelEvaluator(object):    
    cdef decl.IModelEvaluator        *_hndl
    
    cpdef ModelEvalIterator eval(self, 
                        vsc.ModelField root_comp,
                        DataTypeAction root_action)
    
    @staticmethod
    cdef ModelEvaluator mk(decl.IModelEvaluator *)
    
cdef class ModelEvalIterator(object):
    cdef decl.IModelEvalIterator    *_hndl
    
    cpdef bool next(self)
    cpdef type(self)
    cpdef vsc.ModelField action(self)
    cpdef ModelEvalIterator iterator(self)
    
    @staticmethod
    cdef ModelEvalIterator mk(decl.IModelEvalIterator *)
    
cdef class TypeFieldClaim(vsc.TypeField):
    cpdef bool isLock(self)
    
    cdef decl.ITypeFieldClaim *asClaim(self)
    
    @staticmethod
    cdef TypeFieldClaim mk(decl.ITypeFieldClaim *hndl, bool owned=*)
    
cdef class TypeFieldInOut(vsc.TypeField):
    cpdef bool isInput(self)
    
    cdef decl.ITypeFieldInOut *asInOut(self)
    
    @staticmethod
    cdef TypeFieldInOut mk(decl.ITypeFieldInOut *hndl, bool owned=*)

cdef class TypeFieldPool(vsc.TypeField):
    
    cpdef int getDeclSize(self)
    
    cdef decl.ITypeFieldPool *asPool(self)
    
    @staticmethod
    cdef TypeFieldPool mk(decl.ITypeFieldPool *, bool owned=*)
