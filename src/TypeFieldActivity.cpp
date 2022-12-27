/*
 * TypeFieldActivity.cpp
 *
 *  Created on: Jun 17, 2022
 *      Author: mballance
 */

#include "TypeFieldActivity.h"
#include "zsp/arl/dm/IVisitor.h"

namespace zsp {
namespace arl {
namespace dm {


TypeFieldActivity::TypeFieldActivity(
		const std::string		&name,
		IDataTypeActivity		*type,
		bool					owned) :
				TypeField(name, type, owned, vsc::dm::TypeFieldAttr::NoAttr) {

}

TypeFieldActivity::~TypeFieldActivity() {
	// TODO Auto-generated destructor stub
}

IModelActivity *TypeFieldActivity::mkActivity(vsc::dm::IModelBuildContext *ctxt) {
	return getDataTypeT<IDataTypeActivity>()->mkActivity(ctxt, this);
}

void TypeFieldActivity::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<arl::dm::IVisitor *>(v)) {
		dynamic_cast<arl::dm::IVisitor *>(v)->visitTypeFieldActivity(this);
	} else {
		v->visitTypeField(this);
	}
}

}
}
}
