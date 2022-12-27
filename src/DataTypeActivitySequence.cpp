/*
 * DataTypeActivitySequence.cpp
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#include "arl/IContext.h"
#include "arl/IModelActivitySequence.h"
#include "arl/IVisitor.h"
#include "vsc/IModelBuildContext.h"
#include "DataTypeActivitySequence.h"

namespace zsp {
namespace arl {
namespace dm {


DataTypeActivitySequence::DataTypeActivitySequence() : DataTypeActivityScope("") {
	// TODO Auto-generated constructor stub

}

DataTypeActivitySequence::~DataTypeActivitySequence() {
	// TODO Auto-generated destructor stub
}

IModelActivity *DataTypeActivitySequence::mkActivity(
		vsc::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
	IModelActivityScope *ret = ctxt_a->mkModelActivityScope(
		ModelActivityScopeT::Sequence);

	ctxt->pushBottomUpScope(ret);

	for (std::vector<vsc::ITypeFieldUP>::const_iterator
		it=getFields().begin();
		it!=getFields().end(); it++) {
		ret->addField(it->get()->getDataType()->mkTypeField(
			ctxt,
			it->get()));
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

void DataTypeActivitySequence::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitDataTypeActivitySequence(this);
	}
}

}
}
}
