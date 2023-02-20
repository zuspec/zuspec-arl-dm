
import ctypes
cimport debug_mgr.core as dm_core
from zsp_arl_dm cimport decl

from libc.stdint cimport int32_t
from libcpp cimport bool
cimport libvsc_dm.core as vsc
cimport libvsc_dm.decl as vsc_decl

cdef class Factory(object):
    cdef decl.IFactory      *_hndl

    cdef init(self, dm_core.Factory)
    
    cpdef Context mkContext(self, vsc.Context ctxt=*)

cdef class Context(vsc.Context):

    cpdef vsc.ModelField buildModelAction(self, DataTypeAction t, name)
    cpdef ModelFieldComponent buildModelComponent(self, DataTypeComponent t, name)
    cpdef DataTypeAction findDataTypeAction(self, name)
    cpdef DataTypeAction mkDataTypeAction(self, name)
    cpdef DataTypeActivityParallel mkDataTypeActivityParallel(self)
    cpdef DataTypeActivityReplicate mkDataTypeActivityReplicate(self, vsc.TypeExpr count)
    cpdef DataTypeActivitySchedule mkDataTypeActivitySchedule(self)
    cpdef DataTypeActivitySequence mkDataTypeActivitySequence(self)
    cpdef bool addDataTypeAction(self, DataTypeAction)
    cpdef DataTypeActivityTraverse mkDataTypeActivityTraverse(self, vsc.TypeExprFieldRef, vsc.TypeConstraint)
    cpdef DataTypeComponent findDataTypeComponent(self, name)
    cpdef DataTypeComponent mkDataTypeComponent(self, name)
    cpdef bool addDataTypeComponent(self, DataTypeComponent comp_t)
    cpdef DataTypeFlowObj findDataTypeFlowObj(self, name, kind)
    cpdef DataTypeFlowObj mkDataTypeFlowObj(self, name, kind)
    cpdef bool addDataTypeFlowObj(self, DataTypeFlowObj obj_t)

# TODO:    
#    cpdef ModelEvaluator mkModelEvaluator(self)
    cpdef PoolBindDirective mkPoolBindDirective(self, kind, vsc.TypeExprFieldRef pool, vsc.TypeExprFieldRef target)
    cpdef TypeFieldActivity mkTypeFieldActivity(self, name, DataTypeActivity, bool)
    cpdef TypeFieldClaim mkTypeFieldClaim(self, name, vsc.DataType, bool)
    cpdef TypeFieldInOut mkTypeFieldInOut(self, name, vsc.DataType, bool)
    cpdef TypeFieldPool mkTypeFieldPool(self, name, vsc.DataType, bool, vsc.TypeFieldAttr, decl_size)
    
    cdef decl.IContext *asContext(self)
    
    @staticmethod
    cdef mk(decl.IContext *ctxt, bool owned=*)
    
cdef class DataTypeAction(vsc.DataTypeStruct):

    cpdef DataTypeComponent getComponentType(self)
    cpdef setComponentType(self, DataTypeComponent)
    cpdef vsc.TypeFieldRef getCompField(self)
    cpdef addActivity(self, TypeFieldActivity)
    cpdef activities(self)

    cdef decl.IDataTypeAction *asAction(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeAction *, bool owned=*)
    
cdef class DataTypeActivity(object):
    cdef decl.IDataTypeActivity         *_hndl
    cdef bool                           _owned
    
    cdef decl.IDataTypeActivity *asActivity(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivity *, bool owned=*)

cdef class DataTypeActivityScope(DataTypeActivity):
    cpdef name(self)
    cpdef addField(self, vsc.TypeField f)
    cpdef getFields(self)
    cpdef vsc.TypeField getField(self, int32_t idx)
    cpdef addConstraint(self, vsc.TypeConstraint c)
    cpdef getConstraints(self)
    cpdef addActivity(self, TypeFieldActivity)
    cpdef getActivities(self)
    cdef decl.IDataTypeActivityScope *asScope(self)

cdef class DataTypeActivityReplicate(DataTypeActivityScope):
    cpdef vsc.TypeExpr getCount(self)

    cdef decl.IDataTypeActivityReplicate *asReplicate(self)

    @staticmethod
    cdef mk(decl.IDataTypeActivityReplicate *hndl, bool owned=*)

cdef class DataTypeActivityParallel(DataTypeActivityScope):
    cdef decl.IDataTypeActivityParallel *asParallel(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivityParallel *hndl, bool owned=*)
    
cdef class DataTypeActivitySchedule(DataTypeActivityScope):
    cdef decl.IDataTypeActivitySchedule *asSchedule(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivitySchedule *hndl, bool owned=*)
    
cdef class DataTypeActivitySequence(DataTypeActivityScope):
    cdef decl.IDataTypeActivitySequence *asSequence(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivitySequence *hndl, bool owned=*)
    
cdef class DataTypeActivityTraverse(DataTypeActivity):

    cpdef vsc.TypeConstraint getWithC(self)
    
    cpdef setWithC(self, vsc.TypeConstraint c)

    cdef decl.IDataTypeActivityTraverse *asTraverse(self)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivityTraverse *hndl, bool owned=*)
    
    
cdef class DataTypeComponent(vsc.DataTypeStruct):

    cpdef getActionTypes(self)

    cpdef addActionType(self, DataTypeAction action)

    cpdef addPoolBindDirective(self, PoolBindDirective bind)

    cpdef getPoolBindDirectives(self)

    cdef decl.IDataTypeComponent *asComponent(self)
    
    @staticmethod
    cdef DataTypeComponent mk(decl.IDataTypeComponent *, bool owned=*)

cdef class DataTypeFlowObj(vsc.DataTypeStruct):

    cpdef kind(self)

    cdef decl.IDataTypeFlowObj *asFlowObj(self)

    @staticmethod
    cdef DataTypeFlowObj mk(decl.IDataTypeFlowObj *hndl, bool owned=*)

cdef class ModelBuildContext(vsc.ModelBuildContext):
    pass


#cdef class ModelEvaluator(object):    
#    cdef decl.IModelEvaluator        *_hndl
#  
#    cpdef ModelEvalIterator eval(self, 
#                        vsc.RandState       randstate, 
#                        ModelFieldComponent root_comp,
#                        DataTypeAction      root_action)
#    
#    @staticmethod
#    cdef ModelEvaluator mk(decl.IModelEvaluator *)
    
cdef class ModelEvalIterator(object):
    cdef decl.IModelEvalIterator    *_hndl
  
    cpdef bool next(self)
    cpdef type(self)
    cpdef ModelFieldAction action(self)
    cpdef ModelEvalIterator iterator(self)
    
    @staticmethod
    cdef ModelEvalIterator mk(decl.IModelEvalIterator *)

cdef class ModelFieldAction(vsc.ModelField):

    cpdef bool isCompound(self)

    cdef decl.IModelFieldAction *asAction(self)

    @staticmethod
    cdef ModelFieldAction mk(decl.IModelFieldAction *hndl, bool owned=*)
    
cdef class ModelFieldComponent(vsc.ModelField):

    cdef decl.IModelFieldComponent *asComponent(self)
    
    @staticmethod
    cdef ModelFieldComponent mk(decl.IModelFieldComponent *, bool owned=*)

cdef class ModelFieldComponentRoot(ModelFieldComponent):

    cpdef void initCompTree(self)

    cdef decl.IModelFieldComponentRoot *asComponentRoot(self)
    
    @staticmethod
    cdef ModelFieldComponentRoot mk(decl.IModelFieldComponentRoot *, bool owned=*)

cdef class ModelFieldPool(vsc.ModelField):

    cdef decl.IModelFieldPool *asPool(self)

    @staticmethod
    cdef ModelFieldPool mk(decl.IModelFieldPool *hndl, bool owned=*)


cdef class PoolBindDirective(object):
    cdef decl.IPoolBindDirective         *_hndl
    cdef bool                            _owned

    cpdef kind(self)

    cpdef vsc.TypeExprFieldRef getPool(self)

    cpdef vsc.TypeExprFieldRef getTarget(self)

    @staticmethod
    cdef mk(decl.IPoolBindDirective *hndl, bool owned=*)
    
cdef class TypeFieldActivity(vsc.TypeField):

    cdef decl.ITypeFieldActivity *asActivity(self)
    
    @staticmethod
    cdef TypeFieldActivity mk(decl.ITypeFieldActivity *hndl, bool owned=*)

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

cdef class VisitorBase(vsc.VisitorBase):

    cpdef visitDataTypeAction(self, DataTypeAction t)

    cpdef visitDataTypeComponent(self, DataTypeComponent t)

    cpdef visitDataTypeFlowObj(self, DataTypeFlowObj t)

    cpdef visitModelFieldAction(self, ModelFieldAction a)

    cpdef visitModelFieldComponent(self, ModelFieldComponent c)

    cpdef visitModelFieldComponentRoot(self, ModelFieldComponentRoot c)

    cpdef visitModelFieldPool(self, ModelFieldPool f)

cdef class WrapperBuilder(VisitorBase):
    cdef list _obj

    cdef vsc.ObjBase mkObj(self, vsc_decl.IAccept *obj, bool owned)

    cdef _set_obj(self, vsc.ObjBase obj)

cdef class WrapperBuilderVsc(vsc.WrapperBuilder):
    cdef WrapperBuilder            _core

    cdef vsc.ObjBase mkObj(self, vsc_decl.IAccept *obj, bool owned)



