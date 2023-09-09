/*
 * TypeFieldClaim.cpp
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IVisitor.h"
#include "TypeFieldClaim.h"

namespace zsp {
namespace arl {
namespace dm {


TypeFieldClaim::TypeFieldClaim(
			const std::string			&name,
			vsc::dm::IDataType				*type,
			bool						is_lock) :
					TypeField(name, type, false, vsc::dm::TypeFieldAttr::NoAttr),
					m_is_lock(is_lock) {

}

TypeFieldClaim::~TypeFieldClaim() {
	// TODO Auto-generated destructor stub
}

vsc::dm::IModelField *TypeFieldClaim::mkModelField(
		vsc::dm::IModelBuildContext 		*ctxt,
        const vsc::dm::ValRef               &val) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
	return ctxt_a->mkModelFieldClaim(this);
}

void TypeFieldClaim::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<arl::dm::IVisitor *>(v)) {
		dynamic_cast<arl::dm::IVisitor *>(v)->visitTypeFieldClaim(this);
	} else if (v->cascade()) {
		v->visitTypeFieldRef(this);
	}
}

}
}
}
