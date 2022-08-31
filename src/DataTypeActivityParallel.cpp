/*
 * DataTypeActivityParallel.cpp
 *
 * Copyright 2022 Matthew Ballance and Contributors
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

#include "arl/IContext.h"
#include "arl/IVisitor.h"
#include "DataTypeActivityParallel.h"
#include "ModelActivityParallel.h"


namespace arl {
DataTypeActivityParallel::DataTypeActivityParallel() : DataTypeActivityScope("") {

}

DataTypeActivityParallel::~DataTypeActivityParallel() {

}

IModelActivity *DataTypeActivityParallel::mkActivity(
		vsc::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) {
    IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
    IModelActivityParallel *ret = ctxt_a->mkModelActivityParallel();

	for (std::vector<vsc::ITypeFieldUP>::const_iterator
		it=getFields().begin();
		it!=getFields().end(); it++) {
		ret->addField(it->get()->getDataType()->mkTypeField(
			ctxt,
			it->get()));
	}

    ctxt->pushField(ret);
    for (std::vector<ITypeFieldActivity *>::const_iterator
        it=getActivities().begin();
        it!=getActivities().end(); it++) {
        IModelActivity *activity = (*it)->mkActivity(ctxt);
        ret->addBranch(activity);
    }
    ctxt->popField();

    return ret;
}

void DataTypeActivityParallel::accept(vsc::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitDataTypeActivityParallel(this);
    } else if (v->cascade()) {
        v->visitDataTypeStruct(this);
    }
}

}
