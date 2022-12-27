/*
 * DataTypeActivitySchedule.cpp
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IVisitor.h"
#include "vsc/dm/IModelBuildContext.h"
#include "DataTypeActivitySchedule.h"

namespace zsp {
namespace arl {
namespace dm {


DataTypeActivitySchedule::DataTypeActivitySchedule() : DataTypeActivityScope("") {
	// TODO Auto-generated constructor stub

}

DataTypeActivitySchedule::~DataTypeActivitySchedule() {
	// TODO Auto-generated destructor stub
}

IModelActivity *DataTypeActivitySchedule::mkActivity(
		vsc::dm::IModelBuildContext		*ctxt,
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

void DataTypeActivitySchedule::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<arl::dm::IVisitor *>(v)) {
		dynamic_cast<arl::dm::IVisitor *>(v)->visitDataTypeActivitySchedule(this);
	}
}

}
}
}
