/*
 * TypeFieldActivity.cpp
 *
 *  Created on: Jun 17, 2022
 *      Author: mballance
 */

#include "TypeFieldActivity.h"
#include "arl/IVisitor.h"

namespace arl {

TypeFieldActivity::TypeFieldActivity(
		const std::string		&name,
		IDataTypeActivity		*type,
		bool					owned) :
				TypeField(name, type, owned, vsc::TypeFieldAttr::NoAttr) {

}

TypeFieldActivity::~TypeFieldActivity() {
	// TODO Auto-generated destructor stub
}

IModelActivity *TypeFieldActivity::mkActivity(vsc::IModelBuildContext *ctxt) {
	return getDataTypeT<IDataTypeActivity>()->mkActivity(ctxt, this);
}

void TypeFieldActivity::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitTypeFieldActivity(this);
	} else {
		v->visitTypeField(this);
	}
}

} /* namespace arl */
