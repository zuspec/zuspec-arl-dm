
cimport libvsc.decl as vsc

cdef extern from "arl/IContext.h" namespace "arl":
    cdef cppclass IContext(vsc.IContext):
        pass