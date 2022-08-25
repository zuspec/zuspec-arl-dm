/*
 * DataTypeActivitySchedule.cpp
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#include "arl/IContext.h"
#include "arl/IVisitor.h"
#include "vsc/IModelBuildContext.h"
#include "DataTypeActivitySchedule.h"

namespace arl {

DataTypeActivitySchedule::DataTypeActivitySchedule() : DataTypeActivityScope("") {
	// TODO Auto-generated constructor stub

}

DataTypeActivitySchedule::~DataTypeActivitySchedule() {
	// TODO Auto-generated destructor stub
}

IModelActivity *DataTypeActivitySchedule::mkActivity(
		vsc::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
	IModelActivitySchedule *ret = ctxt_a->mkModelActivitySchedule();

	for (std::vector<ITypeFieldActivity *>::const_iterator
		it=getActivities().begin();
		it!=getActivities().end(); it++) {
		IModelActivity *activity = (*it)->mkActivity(ctxt);
		ret->addActivity(activity);
	}

	return ret;
}

void DataTypeActivitySchedule::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitDataTypeActivitySchedule(this);
	}
}

} /* namespace arl */
