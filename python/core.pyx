#****************************************************************************
#* core.pyx
#****************************************************************************
import ctypes
import os
import sys
from ctypes import CDLL
from libc.stdint cimport intptr_t
from libcpp cimport bool
from libcpp.cast cimport dynamic_cast, static_cast
from libcpp.vector cimport vector as cpp_vector
from enum import IntEnum, IntFlag
from typing import List
from zsp_arl_dm cimport decl
cimport vsc_dm.core as vsc
cimport vsc_dm.decl as vsc_decl
cimport cpython.ref as cpy_ref

cdef Factory _inst = None
cdef class Factory(object):

    def __init__(self):
        pass

    cdef init(self, dm_core.Factory f):
        self._hndl.init(f._hndl.getDebugMgr())
        
    cpdef Context mkContext(self, vsc.Context ctxt=None):
        if ctxt is None:
            ctxt = vsc.Factory.inst().mkContext()

        ctxt._owned = False
        return Context.mk(self._hndl.mkContext(ctxt._hndl), True)
    
    @staticmethod
    def inst():
        cdef Factory factory
        global _inst

        if _inst is None:
            ext_dir = os.path.dirname(os.path.abspath(__file__))
            build_dir = os.path.abspath(os.path.join(ext_dir, "../../build"))

            core_lib = None
            libname = "libzsp-arl-dm.so"
            for libdir in ("lib", "lib64"):
                if os.path.isfile(os.path.join(build_dir, libdir, libname)):
                    core_lib = os.path.join(build_dir, libdir, libname)
                    break
            if core_lib is None:
                core_lib = os.path.join(ext_dir, libname)

            if not os.path.isfile(core_lib):
                raise Exception("Extension library core \"%s\" desn't exist" % core_lib)
            so = ctypes.cdll.LoadLibrary(core_lib)

            func = so.zsp_arl_dm_getFactory
            func.restype = ctypes.c_void_p

            hndl = <decl.IFactoryP>(<intptr_t>(func()))
            factory = Factory()
            factory._hndl = hndl
            factory.init(dm_core.Factory.inst())
            _inst = factory
        return _inst


cdef class Context(vsc.Context):

    cpdef DataTypeAction findDataTypeAction(self, name):
        cdef decl.IDataTypeAction *a = self.asContext().findDataTypeAction(name.encode())
        if a != NULL:
            return DataTypeAction.mk(a, False)
        else:
            return None
        
    cpdef DataTypeAction mkDataTypeAction(self, name):
        return DataTypeAction.mk(self.asContext().mkDataTypeAction(name.encode()), True)

#    cpdef DataTypeArlStruct mkDataTypeArlStruct(self, name):
#        return DataTypeArlStruct.mk(self.asContext().mkDataTypeArlStruct(name.encode()), True)

    cpdef DataTypeAddrClaim mkDataTypeAddrClaim(self, name):
        return DataTypeAddrClaim.mk(self.asContext().mkDataTypeAddrClaim(name.encode()), True)

    cpdef DataTypeAddrClaimTransparent mkDataTypeAddrClaimTransparent(self, name):
        return DataTypeAddrClaimTransparent.mk(self.asContext().mkDataTypeAddrClaimTransparent(name.encode()), True)

    cpdef DataTypeFunction findDataTypeFunction(self, name):
        cdef decl.IDataTypeFunction *f = self.asContext().findDataTypeFunction(name.encode())
        if f != NULL:
            return DataTypeFunction.mk(f, False)
        else:
            return None

    cpdef getDataTypeFunctions(self):
        cdef const cpp_vector[decl.IDataTypeFunctionP] *funcs = &self.asContext().getDataTypeFunctions()

        ret = []
        for i in range(funcs.size()):
            ret.append(DataTypeFunction.mk(funcs.at(i), False))

        return ret
    
    cpdef bool addDataTypeAction(self, DataTypeAction a):
        a._owned = False
        return self.asContext().addDataTypeAction(a.asAction())
        
    cpdef DataTypeActivityReplicate mkDataTypeActivityReplicate(self, vsc.TypeExpr count):
        count._owned = False
        return DataTypeActivityReplicate.mk(
            self.asContext().mkDataTypeActivityReplicate(count.asExpr()), 
            True)

    cpdef DataTypeActivityParallel mkDataTypeActivityParallel(self):
        return DataTypeActivityParallel.mk(self.asContext().mkDataTypeActivityParallel(), True)
    
    cpdef DataTypeActivitySchedule mkDataTypeActivitySchedule(self):
        return DataTypeActivitySchedule.mk(self.asContext().mkDataTypeActivitySchedule(), True)
    
    cpdef DataTypeActivitySequence mkDataTypeActivitySequence(self):
        return DataTypeActivitySequence.mk(self.asContext().mkDataTypeActivitySequence(), True)
    
    cpdef DataTypeActivityTraverse mkDataTypeActivityTraverse(self, 
                                    vsc.TypeExprFieldRef    target, 
                                    vsc.TypeConstraint      with_c):
        cdef vsc_decl.ITypeConstraint *with_c_p = NULL

        print("self: %s" % str(self))
        sys.stdout.flush()
        if target is None:
            raise Exception("Target is none")

        target._owned = False
        
        if with_c is not None:
            with_c_p = with_c.asConstraint()
            with_c._owned = False
            
        return DataTypeActivityTraverse.mk(self.asContext().mkDataTypeActivityTraverse(
            target.asFieldRef(),
            with_c_p), True)

    cpdef DataTypeComponent findDataTypeComponent(self, name):
        cdef decl.IDataTypeComponent *c = self.asContext().findDataTypeComponent(name.encode())
        if c != NULL:
            print("Component is non-null")
            return DataTypeComponent.mk(c, False)
        else:
            print("Component is null")
            return None

    cpdef DataTypeComponent mkDataTypeComponent(self, name):
        return DataTypeComponent.mk(
            self.asContext().mkDataTypeComponent(name.encode()), True)
        
    cpdef bool addDataTypeComponent(self, DataTypeComponent comp_t):
        comp_t._owned = False
        return self.asContext().addDataTypeComponent(comp_t.asComponent())

    cpdef DataTypeFlowObj findDataTypeFlowObj(self, name, kind):
        cdef int kind_i = int(kind)
        cdef decl.IDataTypeFlowObj *obj = self.asContext().findDataTypeFlowObj(
            name.encode(), 
            <decl.FlowObjKindE>(kind_i))
        
        if obj != NULL:
            return DataTypeFlowObj.mk(obj, False)
        else:
            return None

    cpdef DataTypeFlowObj mkDataTypeFlowObj(self, name, kind):
        cdef int kind_i = int(kind)
        return DataTypeFlowObj.mk(self.asContext().mkDataTypeFlowObj(
            name.encode(),
            <decl.FlowObjKindE>(kind_i)), True)

    cpdef bool addDataTypeFlowObj(self, DataTypeFlowObj obj_t):
        obj_t._owned = False
        return self.asContext().addDataTypeFlowObj(obj_t.asFlowObj())

# TODO:    
#    cpdef ModelEvaluator mkModelEvaluator(self):
#        return ModelEvaluator.mk(self.asContext().mkModelEvaluator())

    cpdef PoolBindDirective mkPoolBindDirective(self, kind, vsc.TypeExprFieldRef pool, vsc.TypeExprFieldRef target):
        cdef int kind_i = int(kind)
        cdef vsc_decl.ITypeExprFieldRef *tp = NULL

        pool._owned = False

        if target is not None:
            target._owned = False
            tp = target.asFieldRef()

        return PoolBindDirective.mk(self.asContext().mkPoolBindDirective(
            <decl.PoolBindKind>(kind_i),
            pool.asFieldRef(),
            tp), True)

    
    cpdef TypeFieldActivity mkTypeFieldActivity(self, name, DataTypeActivity type, bool owned):
    
        # Ensure we don't try to delete this handle
        if owned:
            type._owned = False
            
        return TypeFieldActivity.mk(
            self.asContext().mkTypeFieldActivity(
                name.encode(),
                type.asActivity(),
                owned), True)
    
    cpdef TypeFieldClaim mkTypeFieldClaim(self, name, vsc.DataType type, bool is_lock):
        return TypeFieldClaim.mk(self.asContext().mkTypeFieldClaim(
            name.encode(),
            type.asType(),
            is_lock), True)
        
    cpdef TypeFieldInOut mkTypeFieldInOut(self, name, vsc.DataType type, bool is_input):
        return TypeFieldInOut.mk(self.asContext().mkTypeFieldInOut(
            name.encode(),
            type.asType(),
            is_input), True)
    
    cpdef TypeFieldPool mkTypeFieldPool(self, name, 
                                        vsc.DataType type, 
                                        bool own,
                                        attr, 
                                        decl_size):
        cdef int attr_i = int(attr)
        cdef vsc_decl.IDataType *type_p = NULL
        
        if type is not None:
            type_p = type.asType()
        else:
            raise Exception("Must specify a type for pool %s" % name)
        
        return TypeFieldPool.mk(self.asContext().mkTypeFieldPool(
            name.encode(),
            type_p,
            own,
            <vsc_decl.TypeFieldAttr>(attr_i),
            decl_size), True)
    
    cdef decl.IContext *asContext(self):
        return dynamic_cast[decl.IContextP](self._hndl)

    @staticmethod
    cdef mk(decl.IContext *hndl, bool owned=True):
        ret = Context()
        ret._hndl = hndl
        ret._owned = owned
        return ret


cdef class DataTypeAction(vsc.DataTypeStruct):

    cpdef DataTypeComponent getComponentType(self):
        return DataTypeComponent.mk(
            self.asAction().getComponentType(),
            False)
    
    cpdef setComponentType(self, DataTypeComponent comp):
        if comp is None:
            raise Exception("setComponentType: comp is None")
        self.asAction().setComponentType(comp.asComponent())

    cpdef vsc.TypeFieldRef getCompField(self):
        return vsc.TypeFieldRef.mk(self.asAction().getCompField(), False)
        
    cpdef addActivity(self, TypeFieldActivity activity):
        activity._owned = False
        self.asAction().addActivity(activity.asActivity())
        
    cpdef activities(self):
        ret = []
        for i in range(self.asAction().activities().size()):
            ret.append(TypeFieldActivity.mk(
                self.asAction().activities().at(i).get(),
                False))
        
        return ret

    cdef decl.IDataTypeAction *asAction(self):
        return dynamic_cast[decl.IDataTypeActionP](self._hndl)
    
    @staticmethod
    cdef DataTypeAction mk(decl.IDataTypeAction *hndl, bool owned=True):
        ret = DataTypeAction()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class DataTypeActivity(object):

    def __dealloc__(self):
        if self._owned and self._hndl != NULL:
            del self._hndl
            pass
            
    cdef decl.IDataTypeActivity *asActivity(self):
        return dynamic_cast[decl.IDataTypeActivityP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivity *hndl, bool owned=True):
        ret = DataTypeActivity()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    

cdef class DataTypeActivityScope(DataTypeActivity):

    cpdef name(self):
        return self.asScope().name().decode()

    cpdef addField(self, vsc.TypeField f):
        f._owned = False
        self.asScope().addField(f.asField())
        
    cpdef getFields(self):
        ret = []
        for i in range(self.asScope().getFields().size()):
            ret.append(vsc.TypeField.mk(
                self.asScope().getFields().at(i).get(), False))
        return ret
    
    cpdef vsc.TypeField getField(self, int32_t idx):
        cdef vsc_decl.ITypeField *ret_h = self.asScope().getField(idx)
        
        if ret_h != NULL:
            return vsc.TypeField.mk(ret_h, False)
        else:
            return None
    
    cpdef addConstraint(self, vsc.TypeConstraint c):
        self.asScope().addConstraint(c.asConstraint())
        pass
    
    cpdef getConstraints(self):
        ret = []
        for i in range(self.asScope().getConstraints().size()):
            ret.append(vsc.TypeConstraint.mk(
                self.asScope().getConstraints().at(i).get(), False))
        return ret
    
    cpdef addActivity(self, TypeFieldActivity activity):
        activity._owned = False
        self.asScope().addActivity(activity.asActivity())
    
    cpdef getActivities(self):
        ret = []
        for i in range(self.asScope().getActivities().size()):
            ret.append(TypeFieldActivity.mk(
                self.asScope().getActivities().at(i).get(),
                False))
            pass
        return ret

    cdef decl.IDataTypeActivityScope *asScope(self):
        return dynamic_cast[decl.IDataTypeActivityScopeP](self._hndl)

cdef class DataTypeActivityReplicate(DataTypeActivityScope):

    cpdef vsc.TypeExpr getCount(self):
        return vsc.TypeExpr.mk(
            self.asReplicate().getCount(),
            False)

    cdef decl.IDataTypeActivityReplicate *asReplicate(self):
        return dynamic_cast[decl.IDataTypeActivityReplicateP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivityReplicate *hndl, bool owned=True):
        ret = DataTypeActivityReplicate()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypeActivityParallel(DataTypeActivityScope):
    cdef decl.IDataTypeActivityParallel *asParallel(self):
        return dynamic_cast[decl.IDataTypeActivityParallelP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivityParallel *hndl, bool owned=True):
        ret = DataTypeActivityParallel()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypeActivitySchedule(DataTypeActivityScope):
    cdef decl.IDataTypeActivitySchedule *asSchedule(self):
        return dynamic_cast[decl.IDataTypeActivityScheduleP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivitySchedule *hndl, bool owned=True):
        ret = DataTypeActivitySchedule()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class DataTypeActivitySequence(DataTypeActivityScope):

    
    cdef decl.IDataTypeActivitySequence *asSequence(self):
        return dynamic_cast[decl.IDataTypeActivitySequenceP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivitySequence *hndl, bool owned=True):
        ret = DataTypeActivitySequence()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class DataTypeActivityTraverse(DataTypeActivity):

    cpdef vsc.TypeConstraint getWithC(self):
        cdef vsc_decl.ITypeConstraint *ch = self.asTraverse().getWithC()
        if ch != NULL:
            return vsc.TypeConstraint.mk(ch, False)
        else:
            return None
    
    cpdef setWithC(self, vsc.TypeConstraint c):
        if c is None:
            self.asTraverse().setWithC(NULL)
        else:
            c._owned = False
            self.asTraverse().setWithC(c.asConstraint())

    cdef decl.IDataTypeActivityTraverse *asTraverse(self):
        return dynamic_cast[decl.IDataTypeActivityTraverseP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivityTraverse *hndl, bool owned=True):
        ret = DataTypeActivityTraverse()
        ret._hndl = hndl
        ret._owned = owned
        return ret    

cdef class DataTypeArlStruct(vsc.DataTypeStruct):
    cdef decl.IDataTypeArlStruct *asArlStruct(self):
        return dynamic_cast[decl.IDataTypeArlStructP](self._hndl)

    @staticmethod
    cdef DataTypeArlStruct mk(decl.IDataTypeArlStruct *hndl, bool owned=True):
        ret = DataTypeArlStruct()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypeAddrClaim(DataTypeArlStruct):

    cdef decl.IDataTypeAddrClaim *asAddrClaim(self):
        return dynamic_cast[decl.IDataTypeAddrClaimP](self._hndl)

    @staticmethod
    cdef DataTypeAddrClaim mk(decl.IDataTypeAddrClaim *hndl, bool owned=True):
        ret = DataTypeAddrClaim()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypeAddrClaimTransparent(DataTypeAddrClaim):

    cdef decl.IDataTypeAddrClaimTransparent *asAddrClaimTransparent(self):
        return dynamic_cast[decl.IDataTypeAddrClaimTransparentP](self._hndl)

    @staticmethod
    cdef DataTypeAddrClaimTransparent mk(decl.IDataTypeAddrClaimTransparent *hndl, bool owned=True):
        ret = DataTypeAddrClaimTransparent()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypeAddrHandle(vsc.DataTypeStruct):

    cdef decl.IDataTypeAddrHandle *asAddrHandle(self):
        return dynamic_cast[decl.IDataTypeAddrHandleP](self._hndl)

    @staticmethod
    cdef DataTypeAddrHandle mk(decl.IDataTypeAddrHandle *hndl, bool owned=True):
        ret = DataTypeAddrHandle()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypeComponent(vsc.DataTypeStruct):

    cpdef getActionTypes(self):
        cdef const cpp_vector[decl.IDataTypeActionP] *atv = &self.asComponent().getActionTypes()
        ret = []
        for i in range(atv.size()):
            ret.append(DataTypeAction.mk(atv.at(i), False))
        return ret

    cpdef addActionType(self, DataTypeAction action):
        self.asComponent().addActionType(action.asAction())

    cpdef addPoolBindDirective(self, PoolBindDirective bind):
        bind._owned = False
        self.asComponent().addPoolBindDirective(bind._hndl)

    cpdef getPoolBindDirectives(self):
        cdef const cpp_vector[decl.IPoolBindDirectiveUP] *bv = &self.asComponent().getPoolBindDirectives()
        ret = []
        for i in range(bv.size()):
            ret.append(PoolBindDirective.mk(bv.at(i).get(), False))
        return ret

    cdef decl.IDataTypeComponent *asComponent(self):
        return dynamic_cast[decl.IDataTypeComponentP](self._hndl)
    
    @staticmethod
    cdef DataTypeComponent mk(decl.IDataTypeComponent *hndl, bool owned=True):
        ret = DataTypeComponent()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypePureComponent(DataTypeComponent):
    cdef decl.IDataTypePureComponent *asPureComponent(self):
        return dynamic_cast[decl.IDataTypePureComponentP](self._hndl)

    @staticmethod
    cdef DataTypePureComponent mk(decl.IDataTypePureComponent *hndl, bool owned=True):
        ret = DataTypePureComponent()
        ret._hndl = hndl
        ret._owned = owned
        return ret
        
cdef class DataTypeReg(DataTypePureComponent):
    cpdef DataTypePackedStruct getDataType(self):
        return DataTypePackedStruct.mk(self.asReg().getDataType(), False)
        
    cpdef uint32_t getOffset(self):
        return self.asReg().getOffset()
        
    cpdef uint32_t getWidth(self):
        return self.asReg().getWidth()
        
    cpdef int getAccess(self):
        return int(self.asReg().getAccess())

    cdef decl.IDataTypeReg *asReg(self):
        return dynamic_cast[decl.IDataTypeRegP](self._hndl)

    @staticmethod
    cdef DataTypeReg mk(decl.IDataTypeReg *hndl, bool owned=True):
        ret = DataTypeReg()
        ret._hndl = hndl
        ret._owned = owned
        return ret

class RegAccess(IntEnum):
    NoAccess = decl.RegAccess_NoAccess
    RW = decl.RegAccess_RW
    RO = decl.RegAccess_RO
    WO = decl.RegAccess_WO
    W1 = decl.RegAccess_W1
    CLR = decl.RegAccess_CLR
    SET = decl.RegAccess_SET

class FlowObjKindE(IntEnum):
    Buffer = decl.FlowObjKindE.Buffer
    Resource = decl.FlowObjKindE.Resource
    State = decl.FlowObjKindE.State
    Stream = decl.FlowObjKindE.Stream

cdef class DataTypeFlowObj(vsc.DataTypeStruct):

    cpdef kind(self):
        cdef int kind_i = int(self.asFlowObj().kind())
        return FlowObjKindE(kind_i)

    cdef decl.IDataTypeFlowObj *asFlowObj(self):
        return dynamic_cast[decl.IDataTypeFlowObjP](self._hndl)

    @staticmethod
    cdef DataTypeFlowObj mk(decl.IDataTypeFlowObj *hndl, bool owned=True):
        ret = DataTypeFlowObj()
        ret._hndl = hndl
        ret._owned = owned
        return ret

class ParamDir(IntEnum):
    In    = decl.ParamDir.In
    Out   = decl.ParamDir.Out
    InOut = decl.ParamDir.InOut

cdef class DataTypeFunctionParamDecl(TypeProcStmtVarDecl):

    cpdef getDirection(self):
        cdef int dir_i = int(self.asParamDecl().getDirection())
        return ParamDir(dir_i)

    cdef decl.IDataTypeFunctionParamDecl *asParamDecl(self):
        return dynamic_cast[decl.IDataTypeFunctionParamDeclP](self._hndl)

    @staticmethod
    cdef DataTypeFunctionParamDecl mk(decl.IDataTypeFunctionParamDecl *hndl, bool owned=True):
        ret = DataTypeFunctionParamDecl()
        ret._hndl = hndl
        ret._owned = owned
        return ret

class DataTypeFunctionFlags(IntFlag):
    NoFlags = decl.DataTypeFunctionFlags.NoFlags
    Solve = decl.DataTypeFunctionFlags.Solve
    Target = decl.DataTypeFunctionFlags.Target
    Core = decl.DataTypeFunctionFlags.Core

cdef class DataTypeFunction(vsc.ObjBase):

    cpdef name(self):
        return self.asFunction().name().decode()

    cpdef vsc.DataType getReturnType(self):
        cdef vsc_decl.IDataType *t = self.asFunction().getReturnType()
        if t == NULL:
            return None
        else:
            return vsc.WrapperBuilder().mkObj(t, False)

    cpdef getParameters(self):
        cdef const cpp_vector[decl.IDataTypeFunctionParamDeclP] *p = &self.asFunction().getParameters()

        ret = []
        for i in range(p.size()):
            ret.append(DataTypeFunctionParamDecl.mk(p.at(i), False))
        return ret

    cpdef getBody(self):
        cdef decl.ITypeProcStmtScope *body = self.asFunction().getBody()
        if body != NULL:
            return vsc.WrapperBuilder().mkObj(body, False)
        else:
            return None

    cpdef getFlags(self):
        cdef int flags_i = int(self.asFunction().getFlags())
        return DataTypeFunctionFlags(flags_i)

    cpdef bool hasFlags(self, flags):
        cdef int flags_i = int(flags)
        return self.asFunction().hasFlags(<decl.DataTypeFunctionFlags>(flags_i))
    
    cpdef object getAssociatedData(self):
        cdef decl.IDataTypeFunction *f = self.asFunction()
        cdef vsc_decl.AssociatedDataClosure *ad
        if f == NULL or f.getAssociatedData() == NULL:
            return None
        else:
            ad = dynamic_cast[vsc_decl.AssociatedDataClosureP](f.getAssociatedData())
        if ad == NULL:
            return None
        else:
            return ad.getData()

    cpdef void setAssociatedData(self, object obj):
        cdef vsc_decl.AssociatedDataClosure *closure = new vsc_decl.AssociatedDataClosure(<cpy_ref.PyObject *>(obj))
        self.asFunction().setAssociatedData(closure)

    cdef decl.IDataTypeFunction *asFunction(self):
        return dynamic_cast[decl.IDataTypeFunctionP](self._hndl)

    @staticmethod
    cdef DataTypeFunction mk(decl.IDataTypeFunction *hndl, bool owned=True):
        ret = DataTypeFunction()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypePyObj(vsc.DataType):
    cdef decl.IDataTypePyObj *asPyObj(self):
        return dynamic_cast[decl.IDataTypePyObjP](self._hndl)

    @staticmethod
    cdef DataTypePyObj mk(decl.IDataTypePyObj *hndl, bool owned=True):
        ret = DataTypePyObj()
        ret._hndl = hndl
        ret._owned = owned
        return ret
        
cdef class DataTypeResource(vsc.DataType):
    cdef decl.IDataTypeResource *asResource(self):
        return dynamic_cast[decl.IDataTypeResourceP](self._hndl)

    @staticmethod
    cdef DataTypeResource mk(decl.IDataTypeResource *hndl, bool owned=True):
        ret = DataTypeResource()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypeTransparentAddrSpace(vsc.DataType):
    cdef decl.IDataTypeTransparentAddrSpace *asTransparentAddrSpace(self):
        return dynamic_cast[decl.IDataTypeTransparentAddrSpaceP](self._hndl)

    @staticmethod
    cdef DataTypeTransparentAddrSpace mk(decl.IDataTypeTransparentAddrSpace *hndl, bool owned=True):
        ret = DataTypeTransparentAddrSpace()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypeCoreLibComponent(DataTypeComponent):
    cdef decl.IDataTypeCoreLibComponent *asCoreLibComponent(self):
        return dynamic_cast[decl.IDataTypeCoreLibComponentP](self._hndl)

    @staticmethod
    cdef DataTypeCoreLibComponent mk(decl.IDataTypeCoreLibComponent *hndl, bool owned=True):
        ret = DataTypeCoreLibComponent()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class DataTypePackedStruct(vsc.DataTypeStruct):

    cdef decl.IDataTypePackedStruct *asPacked(self):
        return dynamic_cast[decl.IDataTypePackedStructP](self._hndl)

    @staticmethod
    cdef DataTypePackedStruct mk(decl.IDataTypePackedStruct *hndl, bool owned=True):
        ret = DataTypePackedStruct()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelBuildContext(vsc.ModelBuildContext):

    def __init__(self, Context ctxt):
        self._hndl = decl.mkModelBuildContextArl(ctxt.asContext())


# cdef class ModelEvaluator(object):
  
#     def __dealloc__(self):
#         if self._hndl != NULL:
#             del self._hndl
          
#     cpdef ModelEvalIterator eval(self, 
#                         vsc.RandState       randstate,
#                         ModelFieldComponent root_comp,
#                         DataTypeAction      root_action):
#         if root_comp is None:
#             raise Exception("None root_comp")
#         if root_action is None:
#             raise Exception("None root_action")

#         cdef decl.IModelEvalIterator *it = self._hndl.eval(
#                 randstate._hndl,
#                 root_comp.asComponent(),
#                 root_action.asAction())
       
#         return ModelEvalIterator.mk(it)
    
#     @staticmethod
#     cdef ModelEvaluator mk(decl.IModelEvaluator *hndl):
#         ret = ModelEvaluator()
#         ret._hndl = hndl
#         return ret

class ModelEvalNodeT(IntEnum):
    Action = decl.ModelEvalNodeT.Action
    Parallel = decl.ModelEvalNodeT.Parallel
    Sequence = decl.ModelEvalNodeT.Sequence

cdef class ModelEvalIterator(object):

    def __dealloc__(self):
        # Iterator memory is self-managed, so the
        # facade doesn't get involved
        pass
            
    cpdef bool next(self):
        if self._hndl == NULL:
            return False

        ret = self._hndl.next()

        # Iterator self-destructs when it's no longer valid
        if not ret:
            self._hndl = NULL 
        return ret
            
    cpdef type(self):
        cdef int type_i
        if self._hndl == NULL:
            return None

        type_i = int(self._hndl.type())
        return ModelEvalNodeT(type_i)
  
    cpdef ModelFieldAction action(self):
        return ModelFieldAction.mk(self._hndl.action(), False)
  
    cpdef ModelEvalIterator iterator(self):
        cdef decl.IModelEvalIterator *it = self._hndl.iterator()
        if it != NULL:
            return ModelEvalIterator.mk(self._hndl.iterator())
        else:
            return None

    @staticmethod
    cdef ModelEvalIterator mk(decl.IModelEvalIterator *hndl):
        ret = ModelEvalIterator()
        ret._hndl = hndl
        return ret

cdef class ModelFieldAction(vsc.ModelField):

    cpdef bool isCompound(self):
        return self.asAction().isCompound()

    cdef decl.IModelFieldAction *asAction(self):
        return dynamic_cast[decl.IModelFieldActionP](self._hndl)

    @staticmethod
    cdef ModelFieldAction mk(decl.IModelFieldAction *hndl, bool owned=True):
        ret = ModelFieldAction()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class ModelFieldComponent(vsc.ModelField):

    cdef decl.IModelFieldComponent *asComponent(self):
        return dynamic_cast[decl.IModelFieldComponentP](self._hndl)
    
    @staticmethod
    cdef ModelFieldComponent mk(decl.IModelFieldComponent *hndl, bool owned=True):
        ret = ModelFieldComponent()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelFieldComponentRoot(ModelFieldComponent):

    cpdef void initCompTree(self):
        self.asComponentRoot().initCompTree()
    
    cdef decl.IModelFieldComponentRoot *asComponentRoot(self):
        return dynamic_cast[decl.IModelFieldComponentRootP](self._hndl)
    
    @staticmethod
    cdef ModelFieldComponentRoot mk(decl.IModelFieldComponentRoot *hndl, bool owned=True):
        ret = ModelFieldComponentRoot()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelFieldExecutor(vsc.ModelField):
    cdef decl.IModelFieldExecutor *asExecutor(self):
        return dynamic_cast[decl.IModelFieldExecutorP](self._hndl)

cdef class ModelFieldPool(vsc.ModelField):
    cdef decl.IModelFieldPool *asPool(self):
        return dynamic_cast[decl.IModelFieldPoolP](self._hndl)

    @staticmethod
    cdef ModelFieldPool mk(decl.IModelFieldPool *hndl, bool owned=True):
        ret = ModelFieldPool()
        ret._hndl = hndl
        ret._owned = owned
        return ret


class PoolBindKind(IntEnum):
    All = decl.PoolBindKind.All
    Ref = decl.PoolBindKind.Ref

cdef class PoolBindDirective(object):

    def __dealloc__(self):
        if self._owned:
            del self._hndl

    cpdef kind(self):
        cdef int kind_i
        kind_i = int(self._hndl.kind())
        return PoolBindKind(kind_i)

    cpdef vsc.TypeExprFieldRef getPool(self):
        return vsc.TypeExprFieldRef.mk(self._hndl.getPool(), False)

    cpdef vsc.TypeExprFieldRef getTarget(self):
        cdef vsc_decl.ITypeExprFieldRef *tp = self._hndl.getTarget()
        if tp != NULL:
            return vsc.TypeExprFieldRef.mk(tp, False)
        else:
            return None

    @staticmethod
    cdef mk(decl.IPoolBindDirective *hndl, bool owned=True):
        ret = PoolBindDirective()
        ret._hndl = hndl
        ret._owned = owned
        return ret

class ExecKindT(IntEnum):
    Body = decl.ExecKindT.ExecBody
    PreSolve = decl.ExecKindT.ExecPostSolve
    PostSolve = decl.ExecKindT.ExecPostSolve

cdef class TypeFieldActivity(vsc.TypeField):

    cdef decl.ITypeFieldActivity *asActivity(self):
        return dynamic_cast[decl.ITypeFieldActivityP](self._hndl)
    
    @staticmethod
    cdef TypeFieldActivity mk(decl.ITypeFieldActivity *hndl, bool owned=True):
        ret = TypeFieldActivity()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class TypeFieldClaim(vsc.TypeField):
    cpdef bool isLock(self):
        return self.asClaim().isLock()
    
    cdef decl.ITypeFieldClaim *asClaim(self):
        return dynamic_cast[decl.ITypeFieldClaimP](self._hndl)
    
    @staticmethod
    cdef TypeFieldClaim mk(decl.ITypeFieldClaim *hndl, bool owned=True):
        ret = TypeFieldClaim()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class TypeFieldInOut(vsc.TypeField):
    cpdef bool isInput(self):
        return self.asInOut().isInput()
    
    cdef decl.ITypeFieldInOut *asInOut(self):
        return dynamic_cast[decl.ITypeFieldInOutP](self._hndl)
    
    @staticmethod
    cdef TypeFieldInOut mk(decl.ITypeFieldInOut *hndl, bool owned=True):
        ret = TypeFieldInOut()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
cdef class TypeFieldPool(vsc.TypeField):
    
    cpdef int getDeclSize(self):
        return self.asPool().getDeclSize()
    
    cdef decl.ITypeFieldPool *asPool(self):
        return dynamic_cast[decl.ITypeFieldPoolP](self._hndl)
    
    @staticmethod
    cdef TypeFieldPool mk(decl.ITypeFieldPool *hndl, bool owned=True):
        ret = TypeFieldPool()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeFieldReg(vsc.TypeField):

    cpdef int getAddrOffset(self):
        return self.asReg().getAddrOffset()

    cpdef void setAddrOffset(self, int off):
        self.asReg().setAddrOffset(off)

    cpdef int getWidth(self):
        return self.asReg().getWidth()

    cdef decl.ITypeFieldReg *asReg(self):
        return dynamic_cast[decl.ITypeFieldRegP](self._hndl)

    @staticmethod
    cdef TypeFieldReg mk(decl.ITypeFieldReg *hndl, bool owned=True):
        ret = TypeFieldReg()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeProcStmt(vsc.ObjBase):
    pass

cdef class TypeProcStmtScope(TypeProcStmt):

    cdef decl.ITypeProcStmtScope *asScope(self):
        return dynamic_cast[decl.ITypeProcStmtScopeP](self._hndl)

    @staticmethod
    cdef TypeProcStmtScope mk(decl.ITypeProcStmtScope *hndl, bool owned=True):
        ret = TypeProcStmtScope()
        ret._hndl = hndl
        ret._owned = owned
        return ret


cdef class TypeProcStmtVarDecl(TypeProcStmt):

    cpdef str name(self):
        return self.asVarDecl().name().decode()

    cpdef vsc.DataType getDataType(self):
        cdef vsc_decl.IDataType *type = self.asVarDecl().getDataType()
        return vsc.WrapperBuilder().mkObj(type, False)

    cpdef vsc.TypeExpr getInit(self):
        cdef vsc_decl.ITypeExpr *i = self.asVarDecl().getInit()
        if i == NULL:
            return None
        else:
            return vsc.TypeExpr.mk(i, False)

    cdef decl.ITypeProcStmtVarDecl *asVarDecl(self):
        return dynamic_cast[decl.ITypeProcStmtVarDeclP](self._hndl)

    @staticmethod
    cdef TypeProcStmtVarDecl mk(decl.ITypeProcStmtVarDecl *hndl, bool owned=True):
        ret = TypeProcStmtVarDecl()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class VisitorBase(vsc.VisitorBase):

    def __init__(self):
        super().__init__()
        self.proxy_l.push_back(new decl.VisitorProxy(<cpy_ref.PyObject *>(self)))
    
    cpdef visitDataTypeAction(self, DataTypeAction t):
        pass

    cpdef visitDataTypePyObj(self, DataTypePyObj t):
        pass

    cpdef visitDataTypeResource(self, DataTypeResource t):
        pass

    cpdef visitDataTypeTransparentAddrSpace(self, DataTypeTransparentAddrSpace t):
        pass

    cpdef visitDataTypeCoreLibComponent(self, DataTypeCoreLibComponent t):
        pass

    cpdef visitTypeProcStmtAssign(self, TypeProcStmtAssign t):
        pass

    cpdef visitTypeProcStmtBreak(self, TypeProcStmtBreak t):
        pass

    cpdef visitTypeProcStmtContinue(self, TypeProcStmtContinue t):
        pass

    cpdef visitTypeProcStmtExpr(self, TypeProcStmtExpr t):
        pass

    cpdef visitTypeProcStmtForeach(self, TypeProcStmtForeach t):
        pass

    cpdef visitTypeProcStmtIfClause(self, TypeProcStmtIfClause t):
        pass

    cpdef visitTypeProcStmtIfElse(self, TypeProcStmtIfElse t):
        pass

    cpdef visitTypeProcStmtMatch(self, TypeProcStmtMatch t):
        pass

    cpdef visitTypeProcStmtRepeat(self, TypeProcStmtRepeat t):
        pass

    cpdef visitTypeProcStmtRepeatWhile(self, TypeProcStmtRepeatWhile t):
        pass

    cpdef visitTypeProcStmtReturn(self, TypeProcStmtReturn t):
        pass

    cpdef visitTypeProcStmtYield(self, TypeProcStmtYield t):
        pass

    cpdef visitDataTypeArlStruct(self, DataTypeArlStruct t):
        pass

    cpdef visitDataTypeAddrClaim(self, DataTypeAddrClaim t):
        pass

    cpdef visitDataTypeAddrClaimTransparent(self, DataTypeAddrClaimTransparent t):
        pass

    cpdef visitDataTypeAddrHandle(self, DataTypeAddrHandle t):
        pass

    cpdef visitDataTypeComponent(self, DataTypeComponent t):
        pass

    cpdef visitDataTypePureComponent(self, DataTypePureComponent t):
        pass

    cpdef visitDataTypeReg(self, DataTypeReg t):
        pass

    cpdef visitDataTypeFlowObj(self, DataTypeFlowObj t):
        pass

    cpdef visitDataTypeFunction(self, DataTypeFunction t):
        pass

    cpdef visitDataTypePackedStruct(self, DataTypePackedStruct t):
        pass

    cpdef visitModelFieldAction(self, ModelFieldAction a):
        pass

    cpdef visitModelFieldComponent(self, ModelFieldComponent c):
        pass

    cpdef visitModelFieldComponentRoot(self, ModelFieldComponentRoot c):
        pass

    cpdef visitModelFieldPool(self, ModelFieldPool f):
        pass
    
    cpdef visitTypeFieldReg(self, TypeFieldReg f):
        pass

    cpdef visitTypeProcStmt(self, TypeProcStmt t):
        pass

    cpdef visitTypeProcStmtScope(self, TypeProcStmtScope t):
        pass

# cdef public void VisitorProxy_visitDataTypeEnum(obj, vsc_decl.IDataTypeEnum *t) with gil:
#     obj.enter()
#     obj.visitDataTypeEnum(vsc.DataTypeEnum.mk(t, False))
#     obj.leave()

# cdef public void VisitorProxy_visitDataTypeInt(obj, vsc_decl.IDataTypeInt *t) with gil:
#     obj.enter()
#     obj.visitDataTypeInt(vsc.DataTypeInt.mk(t, False))
#     obj.leave()

# cdef public void VisitorProxy_visitDataTypeStruct(obj, vsc_decl.IDataTypeStruct *t) with gil:
#     obj.enter()
#     obj.visitDataTypeStruct(DataTypeStruct.mk(t, False))
#     obj.leave()

cdef public void VisitorProxy_visitDataTypePyObj(obj, decl.IDataTypePyObj *t) with gil:
    obj.enter()
    obj.visitDataTypePyObj(DataTypePyObj.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeResource(obj, decl.IDataTypeResource *t) with gil:
    obj.enter()
    obj.visitDataTypeResource(DataTypeResource.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeTransparentAddrSpace(obj, decl.IDataTypeTransparentAddrSpace *t) with gil:
    obj.enter()
    obj.visitDataTypeTransparentAddrSpace(DataTypeTransparentAddrSpace.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeCoreLibComponent(obj, decl.IDataTypeCoreLibComponent *t) with gil:
    obj.enter()
    obj.visitDataTypeCoreLibComponent(DataTypeCoreLibComponent.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypePureComponent(obj, decl.IDataTypePureComponent *t) with gil:
    obj.enter()
    obj.visitDataTypePureComponent(DataTypePureComponent.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeReg(obj, decl.IDataTypeReg *t) with gil:
    obj.enter()
    obj.visitDataTypeReg(DataTypeReg.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeAction(obj, decl.IDataTypeAction *t) with gil:
    obj.enter()
    obj.visitDataTypeAction(DataTypeAction.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeArlStruct(obj, decl.IDataTypeArlStruct *t) with gil:
    obj.enter()
    obj.visitDataTypeArlStruct(DataTypeArlStruct.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeAddrClaim(obj, decl.IDataTypeAddrClaim *t) with gil:
    obj.enter()
    obj.visitDataTypeAddrClaim(DataTypeAddrClaim.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeAddrClaimTransparent(obj, decl.IDataTypeAddrClaimTransparent *t) with gil:
    obj.enter()
    obj.visitDataTypeAddrClaimTransparent(DataTypeAddrClaimTransparent.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeAddrHandle(obj, decl.IDataTypeAddrHandle *t) with gil:
    obj.enter()
    obj.visitDataTypeAddrHandle(DataTypeAddrHandle.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitDataTypeComponent(obj, decl.IDataTypeComponent *t) with gil:
    obj.visitDataTypeComponent(DataTypeComponent.mk(t, False))

cdef public void VisitorProxy_visitDataTypeFlowObj(obj, decl.IDataTypeFlowObj *t) with gil:
    obj.visitDataTypeFlowObj(DataTypeFlowObj.mk(t, False))

cdef public void VisitorProxy_visitDataTypeFunction(obj, decl.IDataTypeFunction *t) with gil:
    obj.visitDataTypeFunction(DataTypeFunction.mk(t, False))

cdef public void VisitorProxy_visitDataTypePackedStruct(obj, decl.IDataTypePackedStruct *t) with gil:
    obj.enter()
    obj.visitDataTypePackedStruct(DataTypePackedStruct.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitModelFieldAction(obj, decl.IModelFieldAction *a) with gil:
    obj.visitModelFieldAction(ModelFieldAction.mk(a, False))

cdef public void VisitorProxy_visitModelFieldComponent(obj, decl.IModelFieldComponent *c) with gil:
    obj.visitModelFieldComponent(ModelFieldComponent.mk(c, False))

cdef public void VisitorProxy_visitModelFieldComponentRoot(obj, decl.IModelFieldComponentRoot *c) with gil:
    obj.visitModelFieldComponentRoot(ModelFieldComponentRoot.mk(c, False))

cdef public void VisitorProxy_visitModelFieldPool(obj, decl.IModelFieldPool *c) with gil:
    obj.visitModelFieldPool(ModelFieldPool.mk(c, False))

cdef public void VisitorProxy_visitTypeFieldReg(obj, decl.ITypeFieldReg *c) with gil:
    obj.visitTypeFieldReg(TypeFieldReg.mk(c, False))

cdef public void VisitorProxy_visitTypeProcStmt(obj, decl.ITypeProcStmt *t) with gil:
#    obj.visitTypeProcStmt(TypeProcStmt.mk(t, False))
    pass

cdef class TypeProcStmtMatchChoice(TypeProcStmt):
    cpdef vsc.TypeExpr getCond(self):
        return vsc.TypeExpr.mk(self.asChoice().getCond(), False)

    cpdef TypeProcStmt getBody(self):
        return vsc.WrapperBuilder().mkObj(self.asChoice().getBody(), False)

    cdef decl.ITypeProcStmtMatchChoice *asChoice(self):
        return dynamic_cast[decl.ITypeProcStmtMatchChoiceP](self._hndl)

    @staticmethod
    cdef TypeProcStmtMatchChoice mk(decl.ITypeProcStmtMatchChoice *hndl, bool owned=True):
        ret = TypeProcStmtMatchChoice()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeProcStmtRepeat(TypeProcStmt):
    cpdef vsc.TypeExpr getExpr(self):
        return vsc.TypeExpr.mk(self.asRepeat().getExpr(), False)

    cpdef TypeProcStmt getBody(self):
        return vsc.WrapperBuilder().mkObj(self.asRepeat().getBody(), False)

    cdef decl.ITypeProcStmtRepeat *asRepeat(self):
        return dynamic_cast[decl.ITypeProcStmtRepeatP](self._hndl)

    @staticmethod
    cdef TypeProcStmtRepeat mk(decl.ITypeProcStmtRepeat *hndl, bool owned=True):
        ret = TypeProcStmtRepeat()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef public void VisitorProxy_visitTypeProcStmtScope(obj, decl.ITypeProcStmtScope *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtScope(TypeProcStmtScope.mk(t, False))
    obj.leave()

cdef class TypeProcStmtAssign(TypeProcStmt):
    cpdef vsc.TypeExpr getLhs(self):
        return vsc.TypeExpr.mk(self.asAssign().getLhs(), False)

    cpdef vsc.TypeExpr getRhs(self):
        return vsc.TypeExpr.mk(self.asAssign().getRhs(), False)

    cdef decl.ITypeProcStmtAssign *asAssign(self):
        return dynamic_cast[decl.ITypeProcStmtAssignP](self._hndl)

    @staticmethod
    cdef TypeProcStmtAssign mk(decl.ITypeProcStmtAssign *hndl, bool owned=True):
        ret = TypeProcStmtAssign()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef public void VisitorProxy_visitTypeProcStmtAssign(obj, decl.ITypeProcStmtAssign *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtAssign(TypeProcStmtAssign.mk(t, False))
    obj.leave()

cdef class TypeProcStmtBreak(TypeProcStmt):
    cdef decl.ITypeProcStmtBreak *asBreak(self):
        return dynamic_cast[decl.ITypeProcStmtBreakP](self._hndl)

    @staticmethod
    cdef TypeProcStmtBreak mk(decl.ITypeProcStmtBreak *hndl, bool owned=True):
        ret = TypeProcStmtBreak()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeProcStmtContinue(TypeProcStmt):
    cdef decl.ITypeProcStmtContinue *asContinue(self):
        return dynamic_cast[decl.ITypeProcStmtContinueP](self._hndl)

    @staticmethod
    cdef TypeProcStmtContinue mk(decl.ITypeProcStmtContinue *hndl, bool owned=True):
        ret = TypeProcStmtContinue()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeProcStmtExpr(TypeProcStmt):
    cpdef vsc.TypeExpr getExpr(self):
        return vsc.TypeExpr.mk(self.asExpr().getExpr(), False)

    cdef decl.ITypeProcStmtExpr *asExpr(self):
        return dynamic_cast[decl.ITypeProcStmtExprP](self._hndl)

    @staticmethod
    cdef TypeProcStmtExpr mk(decl.ITypeProcStmtExpr *hndl, bool owned=True):
        ret = TypeProcStmtExpr()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeProcStmtForeach(TypeProcStmt):

    cdef decl.ITypeProcStmtForeach *asForeach(self):
        return dynamic_cast[decl.ITypeProcStmtForeachP](self._hndl)

    @staticmethod
    cdef TypeProcStmtForeach mk(decl.ITypeProcStmtForeach *hndl, bool owned=True):
        ret = TypeProcStmtForeach()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef public void VisitorProxy_visitTypeProcStmtBreak(obj, decl.ITypeProcStmtBreak *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtBreak(TypeProcStmtBreak.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitTypeProcStmtContinue(obj, decl.ITypeProcStmtContinue *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtContinue(TypeProcStmtContinue.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitTypeProcStmtExpr(obj, decl.ITypeProcStmtExpr *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtExpr(TypeProcStmtExpr.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitTypeProcStmtForeach(obj, decl.ITypeProcStmtForeach *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtForeach(TypeProcStmtForeach.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitTypeProcStmtIfClause(obj, decl.ITypeProcStmtIfClause *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtIfClause(TypeProcStmtIfClause.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitTypeProcStmtIfElse(obj, decl.ITypeProcStmtIfElse *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtIfElse(TypeProcStmtIfElse.mk(t, False))
    obj.leave()

cdef class TypeProcStmtIfClause(TypeProcStmt):
    cpdef vsc.TypeExpr getCond(self):
        return vsc.TypeExpr.mk(self.asIfClause().getCond(), False)

    cpdef TypeProcStmt getStmt(self):
        return vsc.WrapperBuilder().mkObj(self.asIfClause().getStmt(), False)

    cdef decl.ITypeProcStmtIfClause *asIfClause(self):
        return dynamic_cast[decl.ITypeProcStmtIfClauseP](self._hndl)

    @staticmethod
    cdef TypeProcStmtIfClause mk(decl.ITypeProcStmtIfClause *hndl, bool owned=True):
        ret = TypeProcStmtIfClause()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef public void VisitorProxy_visitTypeProcStmtMatchChoice(obj, decl.ITypeProcStmtMatchChoice *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtMatchChoice(TypeProcStmtMatchChoice.mk(t, False))
    obj.leave()

cdef class TypeProcStmtMatch(TypeProcStmt):
    cpdef vsc.TypeExpr getCond(self):
        return vsc.TypeExpr.mk(self.asMatch().getCond(), False)

    cpdef getChoices(self):
        cdef const cpp_vector[decl.ITypeProcStmtMatchChoiceUP] *choices = &self.asMatch().getChoices()
        ret = []
        for i in range(choices.size()):
            ret.append(TypeProcStmtMatchChoice.mk(choices.at(i).get(), False))
        return ret

    cdef decl.ITypeProcStmtMatch *asMatch(self):
        return dynamic_cast[decl.ITypeProcStmtMatchP](self._hndl)

    @staticmethod
    cdef TypeProcStmtMatch mk(decl.ITypeProcStmtMatch *hndl, bool owned=True):
        ret = TypeProcStmtMatch()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class TypeProcStmtIfElse(TypeProcStmt):
    cpdef getIfClauses(self):
        cdef const cpp_vector[decl.ITypeProcStmtIfClauseUP] *clauses = &self.asIfElse().getIfClauses()
        ret = []
        for i in range(clauses.size()):
            ret.append(TypeProcStmtIfClause.mk(clauses.at(i).get(), False))
        return ret

    cpdef TypeProcStmt getElseClause(self):
        cdef decl.ITypeProcStmt *else_stmt = self.asIfElse().getElseClause()
        if else_stmt != NULL:
            return vsc.WrapperBuilder().mkObj(else_stmt, False)
        else:
            return None

    cdef decl.ITypeProcStmtIfElse *asIfElse(self):
        return dynamic_cast[decl.ITypeProcStmtIfElseP](self._hndl)

    @staticmethod
    cdef TypeProcStmtIfElse mk(decl.ITypeProcStmtIfElse *hndl, bool owned=True):
        ret = TypeProcStmtIfElse()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef public void VisitorProxy_visitTypeProcStmtMatch(obj, decl.ITypeProcStmtMatch *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtMatch(TypeProcStmtMatch.mk(t, False))
    obj.leave()

cdef class TypeProcStmtRepeatWhile(TypeProcStmt):
    cpdef vsc.TypeExpr getExpr(self):
        return vsc.TypeExpr.mk(self.asRepeatWhile().getExpr(), False)

    cpdef TypeProcStmt getBody(self):
        return vsc.WrapperBuilder().mkObj(self.asRepeatWhile().getBody(), False)

    cdef decl.ITypeProcStmtRepeatWhile *asRepeatWhile(self):
        return dynamic_cast[decl.ITypeProcStmtRepeatWhileP](self._hndl)

    @staticmethod
    cdef TypeProcStmtRepeatWhile mk(decl.ITypeProcStmtRepeatWhile *hndl, bool owned=True):
        ret = TypeProcStmtRepeatWhile()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef public void VisitorProxy_visitTypeProcStmtRepeat(obj, decl.ITypeProcStmtRepeat *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtRepeat(TypeProcStmtRepeat.mk(t, False))
    obj.leave()

cdef class TypeProcStmtReturn(TypeProcStmt):
    cpdef vsc.TypeExpr getExpr(self):
        return vsc.TypeExpr.mk(self.asReturn().getExpr(), False)

    cdef decl.ITypeProcStmtReturn *asReturn(self):
        return dynamic_cast[decl.ITypeProcStmtReturnP](self._hndl)

    @staticmethod
    cdef TypeProcStmtReturn mk(decl.ITypeProcStmtReturn *hndl, bool owned=True):
        ret = TypeProcStmtReturn()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef public void VisitorProxy_visitTypeProcStmtRepeatWhile(obj, decl.ITypeProcStmtRepeatWhile *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtRepeatWhile(TypeProcStmtRepeatWhile.mk(t, False))
    obj.leave()

cdef public void VisitorProxy_visitTypeProcStmtReturn(obj, decl.ITypeProcStmtReturn *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtReturn(TypeProcStmtReturn.mk(t, False))
    obj.leave()

cdef class TypeProcStmtYield(TypeProcStmt):
    cdef decl.ITypeProcStmtYield *asYield(self):
        return dynamic_cast[decl.ITypeProcStmtYieldP](self._hndl)

    @staticmethod
    cdef TypeProcStmtYield mk(decl.ITypeProcStmtYield *hndl, bool owned=True):
        ret = TypeProcStmtYield()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef public void VisitorProxy_visitTypeProcStmtYield(obj, decl.ITypeProcStmtYield *t) with gil:
    obj.enter()
    obj.visitTypeProcStmtYield(TypeProcStmtYield.mk(t, False))
    obj.leave()


cdef class WrapperBuilder(VisitorBase):

    def __init__(self):
        super().__init__()
        self._obj = []

    cdef vsc.ObjBase mkObj(self, vsc_decl.IAccept *obj, bool owned):
        cdef vsc.ObjBase ret = None

        self._obj.append(None)
        self.visitAccept(obj)
        ret = self._obj.pop()

        if ret is not None:
            ret._owned = owned

        return ret

    cdef _set_obj(self, vsc.ObjBase obj):
        self._obj[-1] = obj

    cpdef visitDataTypeAction(self, DataTypeAction t):
        self._set_obj(t)

    cpdef visitDataTypeArlStruct(self, DataTypeArlStruct t):
        self._set_obj(t)

    cpdef visitDataTypeAddrClaim(self, DataTypeAddrClaim t):
        self._set_obj(t)

    cpdef visitDataTypeAddrClaimTransparent(self, DataTypeAddrClaimTransparent t):
        self._set_obj(t)

    cpdef visitDataTypeAddrHandle(self, DataTypeAddrHandle t):
        self._set_obj(t)

    cpdef visitDataTypeComponent(self, DataTypeComponent t):
        self._set_obj(t)

    cpdef visitDataTypeFlowObj(self, DataTypeFlowObj t):
        self._set_obj(t)

    cpdef visitDataTypePackedStruct(self, DataTypePackedStruct t):
        self._set_obj(t)
        
    cpdef visitDataTypePyObj(self, DataTypePyObj t):
        self._set_obj(t)

    cpdef visitDataTypeResource(self, DataTypeResource t):
        self._set_obj(t)

    cpdef visitDataTypeTransparentAddrSpace(self, DataTypeTransparentAddrSpace t):
        self._set_obj(t)

    cpdef visitDataTypeCoreLibComponent(self, DataTypeCoreLibComponent t):
        self._set_obj(t)

    cpdef visitDataTypePureComponent(self, DataTypePureComponent t):
        self._set_obj(t)

    cpdef visitDataTypeReg(self, DataTypeReg t):
        self._set_obj(t)

    cpdef visitModelFieldAction(self, ModelFieldAction a):
        print("visitModelFieldAction")
        self._set_obj(a)

    cpdef visitModelFieldComponent(self, ModelFieldComponent c):
        self._set_obj(c)

    cpdef visitModelFieldComponentRoot(self, ModelFieldComponentRoot c):
        self._set_obj(c)

    cpdef visitModelFieldPool(self, ModelFieldPool f):
        print("visitModelFieldPool")
        self._set_obj(f)
    
    cpdef visitTypeFieldReg(self, TypeFieldReg f):
        print("visitTypeFieldReg")
        self._set_obj(f)

    cpdef visitTypeProcStmt(self, TypeProcStmt t):
        # This is a no-op, since we don't have a wrapper for TypeProcStmt
        pass
    
    cpdef visitTypeProcStmtScope(self, TypeProcStmtScope t):
        self._set_obj(t)

cdef class WrapperBuilderVsc(vsc.WrapperBuilder):

    def __init__(self):
        self._core = WrapperBuilder()

    cdef vsc.ObjBase mkObj(self, vsc_decl.IAccept *obj, bool owned):
        return self._core.mkObj(obj, owned);


vsc.addWrapperBuilder(WrapperBuilderVsc())
