#****************************************************************************
#* py_val_to_val_ref.py
#*
#* Copyright 2023 Matthew Ballance and Contributors
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

class PyValToValRef(object):

    def __init__(self, ctxt):
        self._ctxt = ctxt

    def toValRef(self, v):
        ret = None
        if type(v) == int:
            is_signed = (v < 0)
            if v > 0xFFFFFFFF:
                width = 64
            elif v > 0xFFFF:
                width = 32
            elif v > 0xFF:
                width = 16
            else:
                width = 8
            ret = self._ctxt.mkValRefInt(v, is_signed, width)
        else:
            raise Exception("Unknown value type %s" % str(v))
        print("v=%s ret=%s" % (str(v), str(ret)))
        return ret


