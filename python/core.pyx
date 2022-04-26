
import os
from ctypes import CDLL
from libcpp cimport bool
from libcpp.cast cimport dynamic_cast
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

    cpdef vsc.ModelField buildModelComponent(self, DataTypeComponent t):
        cdef vsc_decl.IModelField *f = self.asContext().buildModelComponent(t.asComponent())
        return 
        pass
    
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
    
    cdef decl.IContext *asContext(self):
        return dynamic_cast[decl.IContextP](self._hndl)

    @staticmethod
    cdef mk(decl.IContext *hndl, bool owned=True):
        ret = Context()
        ret._hndl = hndl
        ret._owned = owned
        return ret


cdef class DataTypeAction(vsc.DataTypeStruct):

    cdef decl.IDataTypeAction *asAction(self):
        return dynamic_cast[decl.IDataTypeActionP](self._hndl)
    
    @staticmethod
    cdef DataTypeAction mk(decl.IDataTypeAction *hndl, bool owned=True):
        ret = DataTypeAction()
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
    
