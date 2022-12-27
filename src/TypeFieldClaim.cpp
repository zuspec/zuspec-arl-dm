/*
 * TypeFieldClaim.cpp
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */
#include "arl/IContext.h"
#include "arl/IVisitor.h"
#include "TypeFieldClaim.h"

namespace zsp {
namespace arl {
namespace dm {


TypeFieldClaim::TypeFieldClaim(
			const std::string			&name,
			vsc::IDataType				*type,
			bool						is_lock) :
					TypeField(name, type, false, vsc::TypeFieldAttr::NoAttr),
					m_is_lock(is_lock) {

}

TypeFieldClaim::~TypeFieldClaim() {
	// TODO Auto-generated destructor stub
}

vsc::IModelField *TypeFieldClaim::mkModelField(
		vsc::IModelBuildContext 			*ctxt) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
	return ctxt_a->mkModelFieldClaim(this);
}

void TypeFieldClaim::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitTypeFieldClaim(this);
	} else if (v->cascade()) {
		v->visitTypeFieldRef(this);
	}
}

}
}
}
