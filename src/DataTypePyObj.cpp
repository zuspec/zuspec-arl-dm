/*
 * DataTypePyObj.cpp
 *
 * Copyright 2023 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author:
 */
#include "vsc/dm/impl/ValRefInt.h"
#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "vsc/dm/impl/ValRefPtr.h"
#include "zsp/arl/dm/IVisitor.h"
#include "zsp/arl/dm/IModelBuildContext.h"
#include "DataTypePyObj.h"


namespace zsp {
namespace arl {
namespace dm {


DataTypePyObj::DataTypePyObj(IContext *ctxt) : 
    DataTypeArl(vsc::dm::ValRefInt::native_sz()), m_ctxt(ctxt) {

}

DataTypePyObj::~DataTypePyObj() {

}

void DataTypePyObj::initVal(vsc::dm::ValRef &v) {
    vsc::dm::IValOps *ops = m_ctxt->getValOps(DataTypeKind::PyObj);
    if (ops) {
        ops->initVal(v);
    } else {
        // TODO:

    }
}

void DataTypePyObj::finiVal(vsc::dm::ValRef &v) {
    vsc::dm::IValOps *ops = m_ctxt->getValOps(DataTypeKind::PyObj);
    if (ops) {
        ops->finiVal(v);
    } else {
        // TODO:

    }
}

vsc::dm::ValRef DataTypePyObj::copyVal(const vsc::dm::ValRef &src) {
    vsc::dm::IValOps *ops = m_ctxt->getValOps(DataTypeKind::PyObj);
    if (ops) {
        return ops->copyVal(src);
    } else {
        // TODO:
    }
    return vsc::dm::ValRef();
}

vsc::dm::IModelField *DataTypePyObj::mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			    &name,
		bool						    is_ref) {
	vsc::dm::IModelField *ret = 0;
    IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());

	if (is_ref) {
		ret = ctxt->ctxt()->mkModelFieldRefRoot(this, name);
	} else {
		ret = ctxt->ctxt()->mkModelFieldRoot(
            this, 
            name, 
            ctxt_a->mkValPyObj(0));
	}

	return ret;
}

vsc::dm::IModelField *DataTypePyObj::mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type,
        const vsc::dm::ValRef           &val) {
	vsc::dm::IModelField *ret;

	if (vsc::dm::TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
        vsc::dm::ValRefInt val_p(val);
		ret = ctxt->ctxt()->mkModelFieldType(type, val_p);
	}

	return ret;
}

void DataTypePyObj::accept(vsc::dm::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitDataTypePyObj(this);
    } else if (v->cascade()) {
//        v->visitDataType(this);
    }
}

}
}
}
