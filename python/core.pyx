
import os
import sys
from ctypes import CDLL
from libcpp cimport bool
from libcpp.cast cimport dynamic_cast
from enum import IntEnum
from libarl cimport decl
cimport libvsc.core as vsc
cimport libvsc.decl as vsc_decl

cdef Arl _Arl_inst = None
cdef class Arl(object):

    def __init__(self):
        
        self._vsc = vsc.Vsc.inst()
        path = "abc"
        print("core file: %s" % str(os.path.abspath(__file__)))
        paths = []
        paths_s = set()
        # These are libraries that we know are pointless to search
        excludes = ['libgcc', 'libstdc++', 'libc', 'libdl', 'libz', 'libm', 'libutil', 'libpthread', 'ld-', 'libpython']
        with open("/proc/%d/maps" % os.getpid(), "r") as fp:
            while True:
                line = fp.readline()
                
                if not line:
                    break
               
                line = line.strip()

                idx = line.find('/')
                if idx != -1:                
                    path = line[idx:]
                    
                    if not os.path.isfile(path):
                        # File doesn't exist, which probably means that
                        # the path wraps around to the next line
                        line = fp.readline().strip()
                        
                        path += line
                        
                    if path.rfind('.so') != -1:
                        if path not in paths_s:
                            exclude = False
                            for e in excludes:
                                if path.find(e) != -1:
                                    exclude = True
                                    break

                            paths_s.add(path)
                            if not exclude:                                
                                paths.append(path)

        print("Paths: %s" % str(paths))
        
        lib_path = None
        
        for p in filter(lambda x : x.find('arl') != -1, paths):
            lib = CDLL(p)
            try:
                getattr(lib, 'iarl')
                lib_path = p
                print("Found iarl")
                break
            except Exception as e:
                pass
            
        if lib_path is None:
            for p in filter(lambda x : x.find('arl') == -1, paths):
                lib = CDLL(p)
                try:
                    getattr(lib, 'iarl')
                    lib_path = p
                    print("Found iarl")
                    break
                except Exception as e:
                    pass

        # Nothing already loaded provides tblink, so load the core library
        if lib_path is None:
            lib_dir = os.path.dirname(os.path.abspath(__file__))
            lib_path = os.path.join(lib_dir, "libarl.so")
            
        print("lib_path: %s" % lib_path)
        self._hndl = decl.py_get_arl(lib_path.encode())
        
        if self._hndl == NULL:
            raise Exception("Failed to load libarl core library")        

        # Initialize the library with the debug manager
        self._hndl.init(self._vsc._hndl.getDebugMgr())
        pass
    
    cpdef Context mkContext(self):
        return Context.mk(self._hndl.mkContext(
            self._vsc._hndl.mkContext()
            ), True)
    
    @staticmethod
    def inst():
        global _Arl_inst
        if _Arl_inst is None:
            _Arl_inst = Arl()
        return _Arl_inst
        


cdef class Context(vsc.Context):

    cpdef vsc.ModelField buildModelAction(self, DataTypeAction t, name):
        return vsc.ModelField.mk(self.asContext().buildModelAction(
            t.asAction(), name.encode()), True)

    cpdef ModelFieldRootComponent buildModelComponent(self, DataTypeComponent t, name):
        return ModelFieldRootComponent.mk(
            self.asContext().buildModelComponent(
                t.asComponent(), name.encode()), 
            True)
    
    cpdef DataTypeAction findDataTypeAction(self, name):
        cdef decl.IDataTypeAction *a = self.asContext().findDataTypeAction(name.encode())
        if a != NULL:
            return DataTypeAction.mk(a, False)
        else:
            return None
        
    cpdef DataTypeAction mkDataTypeAction(self, name):
        return DataTypeAction.mk(self.asContext().mkDataTypeAction(name.encode()), True)
    
    cpdef bool addDataTypeAction(self, DataTypeAction a):
        a._owned = False
        return self.asContext().addDataTypeAction(a.asAction())
    
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
            with_c_p = with_c._hndl
            with_c._owned = False
            
        return DataTypeActivityTraverse.mk(self.asContext().mkDataTypeActivityTraverse(
            target.asFieldRef(),
            with_c_p), True)

    cpdef DataTypeComponent findDataTypeComponent(self, name):
        cdef decl.IDataTypeComponent *c = self.asContext().findDataTypeComponent(name.encode())
        if c != NULL:
            return DataTypeComponent.mk(c, False)
        else:
            return None

    cpdef DataTypeComponent mkDataTypeComponent(self, name):
        return DataTypeComponent.mk(
            self.asContext().mkDataTypeComponent(name.encode()), True)
        
    cpdef bool addDataTypeComponent(self, DataTypeComponent comp_t):
        comp_t._owned = False
        return self.asContext().addDataTypeComponent(comp_t.asComponent())
    
    cpdef ModelEvaluator mkModelEvaluator(self):
        return ModelEvaluator.mk(self.asContext().mkModelEvaluator())
    
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
            type._hndl,
            is_lock), True)
        
    cpdef TypeFieldInOut mkTypeFieldInOut(self, name, vsc.DataType type, bool is_input):
        return TypeFieldInOut.mk(self.asContext().mkTypeFieldInOut(
            name.encode(),
            type._hndl,
            is_input), True)
    
    cpdef TypeFieldPool mkTypeFieldPool(self, name, 
                                        vsc.DataType type, 
                                        attr, 
                                        decl_size):
        cdef int attr_i = int(attr)
        cdef vsc_decl.IDataType *type_p = NULL
        
        if type is not None:
            type_p = type._hndl
        else:
            raise Exception("Must specify a type for pool %s" % name)
        
        return TypeFieldPool.mk(self.asContext().mkTypeFieldPool(
            name.encode(),
            type_p,
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
        self.asAction().setComponentType(comp.asComponent())
        
    cpdef addActivity(self, TypeFieldActivity activity):
        activity._owned = False
        self.asAction().addActivity(activity.asActivity())
        
    cpdef activities(self):
        ret = []
        for i in range(self.asAction().activities().size()):
            ret.append(TypeFieldActivity.mk(
                self.asAction().activities().at(i),
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
        self.asScope().addField(f._hndl)
        
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
        self.asScope().addConstraint(c._hndl)
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
    
    cpdef activities(self):
        pass

    cdef decl.IDataTypeActivityScope *asScope(self):
        return dynamic_cast[decl.IDataTypeActivityScopeP](self._hndl)

    
    pass

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
            self.asTraverse().setWithC(c._hndl)

    cdef decl.IDataTypeActivityTraverse *asTraverse(self):
        return dynamic_cast[decl.IDataTypeActivityTraverseP](self._hndl)
    
    @staticmethod
    cdef mk(decl.IDataTypeActivityTraverse *hndl, bool owned=True):
        ret = DataTypeActivityTraverse()
        ret._hndl = hndl
        ret._owned = owned
        return ret    

cdef class DataTypeComponent(vsc.DataTypeStruct):

    cdef decl.IDataTypeComponent *asComponent(self):
        return dynamic_cast[decl.IDataTypeComponentP](self._hndl)
    
    @staticmethod
    cdef DataTypeComponent mk(decl.IDataTypeComponent *hndl, bool owned=True):
        ret = DataTypeComponent()
        ret._hndl = hndl
        ret._owned = owned
        return ret

cdef class ModelEvaluator(object):
    
    def __dealloc__(self):
        if self._hndl != NULL:
            del self._hndl
            
    cpdef ModelEvalIterator eval(self, 
                        vsc.ModelField root_comp,
                        DataTypeAction root_action):
        cdef decl.IModelEvalIterator *it = self._hndl.eval(
                root_comp._hndl,
                root_action.asAction())
        
        return ModelEvalIterator.mk(it)
    
    @staticmethod
    cdef ModelEvaluator mk(decl.IModelEvaluator *hndl):
        ret = ModelEvaluator()
        ret._hndl = hndl
        return ret

class ModelEvalNodeT(IntEnum):
    Action = decl.ModelEvalNodeT.Action
    Parallel = decl.ModelEvalNodeT.Parallel
    Sequence = decl.ModelEvalNodeT.Sequence

cdef class ModelEvalIterator(object):

    def __dealloc__(self):
        if self._hndl != NULL:
            del self._hndl
            
    cpdef bool next(self):
        ret = self._hndl.next()
        # Iterator self-destructs when it's no longer valid
        if not ret:
            self._hndl = NULL 
        return ret
            
    cpdef type(self):
        cdef int type_i
        type_i = int(self._hndl.type())
        return ModelEvalNodeT(type_i)
    
    cpdef vsc.ModelField action(self):
        return vsc.ModelField.mk(self._hndl.action(), False)
    
    cpdef ModelEvalIterator iterator(self):
        return ModelEvalIterator.mk(self._hndl.iterator())

    @staticmethod
    cdef ModelEvalIterator mk(decl.IModelEvalIterator *hndl):
        ret = ModelEvalIterator()
        ret._hndl = hndl
        return ret
    
cdef class ModelFieldRootComponent(vsc.ModelField):
    
    cdef decl.IModelFieldRootComponent *asRootComponent(self):
        return dynamic_cast[decl.IModelFieldRootComponentP](self._hndl)
    
    @staticmethod
    cdef ModelFieldRootComponent mk(decl.IModelFieldRootComponent *hndl, bool owned=True):
        ret = ModelFieldRootComponent()
        ret._hndl = hndl
        ret._owned = owned
        return ret
    
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
    