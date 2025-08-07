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

#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IVisitor.h"
#include "DataTypeActivityParallel.h"
#include "ModelActivityParallel.h"


namespace zsp {
namespace arl {
namespace dm {

DataTypeActivityParallel::DataTypeActivityParallel() : DataTypeActivityScope("") {

}

DataTypeActivityParallel::~DataTypeActivityParallel() {

}

IModelActivity *DataTypeActivityParallel::mkActivity(
		vsc::dm::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) {
    IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
    IModelActivityScope *ret = ctxt_a->mkModelActivityScope(
        ModelActivityScopeT::Parallel);

	for (std::vector<vsc::dm::ITypeFieldUP>::const_iterator
		it=getFields().begin();
		it!=getFields().end(); it++) {
        vsc::dm::ValRef todo;
		ret->addField(it->get()->getDataType()->mkTypeField(
			ctxt,
			it->get(),
            todo));
	}

    fprintf(stdout, "Parallel: %zu activities\n", getActivities().size());

    ctxt->pushBottomUpScope(ret);
    for (std::vector<ITypeFieldActivityUP>::const_iterator
        it=getActivities().begin();
        it!=getActivities().end(); it++) {
        IModelActivity *activity = (*it)->mkActivity(ctxt);
        ret->addActivity(activity);
    }
    ctxt->popBottomUpScope();

    return ret;
}

void DataTypeActivityParallel::accept(vsc::dm::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitDataTypeActivityParallel(this);
    } else if (v->cascade()) {
        v->visitDataTypeStruct(this);
    }
}

}
}
}
