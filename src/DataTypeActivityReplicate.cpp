/*
 * DataTypeActivityReplicate.cpp
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
#include "vsc/impl/TaskBuildModelExpr.h"
#include "vsc/impl/TaskBuildModelConstraint.h"
#include "DataTypeActivityReplicate.h"
#include "ModelActivityReplicate.h"

namespace arl {


DataTypeActivityReplicate::DataTypeActivityReplicate(
    IContext            *ctxt,
    vsc::ITypeExpr      *count) : DataTypeActivityScope(""), m_count(count) {

    vsc::IDataTypeInt *ui16 = ctxt->findDataTypeInt(false, 16);
    if (!ui16) {
        ui16 = ctxt->mkDataTypeInt(false, 16);
        ctxt->addDataTypeInt(ui16);
    }

    addField(ctxt->mkTypeFieldPhy("__count", ui16, false,
        vsc::TypeFieldAttr::Rand, 0));
    addField(ctxt->mkTypeFieldPhy("__index", ui16, false,
        vsc::TypeFieldAttr::NoAttr, 0));

    vsc::ITypeExprFieldRef *count_r = ctxt->mkTypeExprFieldRef();
    count_r->addIdxRef(0);
    count_r->addActiveScopeRef(-1);
    addConstraint(ctxt->mkTypeConstraintExpr(
        ctxt->mkTypeExprBin(
            count_r,
            vsc::BinOp::Eq,
            count
        )
    ));

    fprintf(stdout, "EQ=%d\n", vsc::BinOp::Eq);
}

DataTypeActivityReplicate::~DataTypeActivityReplicate() {

}

IModelActivity *DataTypeActivityReplicate::mkActivity(
		vsc::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
    IModelActivityScope *ret = ctxt_a->mkModelActivityReplicate(
        vsc::TaskBuildModelExpr(ctxt).build(m_count)
    );

    ctxt->pushBottomUpScope(ret);

	for (std::vector<vsc::ITypeFieldUP>::const_iterator
		it=getFields().begin();
		it!=getFields().end(); it++) {
		ret->addField(it->get()->getDataType()->mkTypeField(
			ctxt,
			it->get()));
	}

    for (std::vector<vsc::ITypeConstraintUP>::const_iterator
        it=getConstraints().begin();
        it!=getConstraints().end(); it++) {
        ret->addConstraint(vsc::TaskBuildModelConstraint<>(ctxt).build(it->get()));
    }

	fprintf(stdout, "mkActivity: %d\n", getActivities().size());
	for (std::vector<ITypeFieldActivity *>::const_iterator
		it=getActivities().begin();
		it!=getActivities().end(); it++) {
		IModelActivity *field_a = (*it)->mkActivity(ctxt);
		ret->addActivity(field_a);
	}

    ctxt->popBottomUpScope();

    return ret;
}

void DataTypeActivityReplicate::accept(vsc::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitDataTypeActivityReplicate(this);
    } else if (v->cascade()) {
        v->visitDataTypeStruct(this);
    }
}

}
