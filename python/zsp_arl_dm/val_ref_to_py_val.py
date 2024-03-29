#****************************************************************************
#* val_ref_to_py_val.py
#*
#* Copyright 2022 Matthew Ballance and Contributors
#*
#* Licensed under the Apache License, Version 2.0 (the "License"); you may 
#* not use this file except in compliance with the License.  
#* You may obtain a copy of the License at:
#*
#*   http://www.apache.org/licenses/LICENSE-2.0
#*
#* Unless required by applicable law or agreed to in writing, software 
#* distributed under the License is distributed on an "AS IS" BASIS, 
#* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
#* See the License for the specific language governing permissions and 
#* limitations under the License.
#*
#* Created on:
#*     Author: 
#*
#****************************************************************************
import vsc_dm.core as vsc
from zsp_arl_dm.core import VisitorBase

class ValRefToPyVal(VisitorBase):

    def __init__(self, thread):
        super().__init__()
        self._ref = None
        self._val = None
        self._thread = thread
        pass

    def toPyVal(self, v : vsc.ValRef):
        if not v.valid():
            raise Exception("ValRef is not valid")

        vt = v.type()
        if vt is None:
            raise Exception("ValRef does not have a type")

        self._ref = v

        self.visit(vt)
        
        return self._val
    
    def visitDataTypeAddrHandle(self, i):
        print("AddrHandle")
        val = self._thread.getAddrHandleValue(self._ref)
        self._val = val.get_val_u()

    def visitDataTypeInt(self, i):
        vi = vsc.ValRefInt.fromValRef(self._ref)
        if vi.is_signed():
            self._val = vi.get_val_s()
        else:
            self._val = vi.get_val_u()
