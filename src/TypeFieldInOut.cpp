/*
 * TypeFieldInOut.cpp
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IVisitor.h"
#include "vsc/dm/IModelBuildContext.h"
#include "ModelFieldInOut.h"
#include "TypeFieldInOut.h"

namespace zsp {
namespace arl {
namespace dm {


TypeFieldInOut::TypeFieldInOut(
			const std::string		&name,
			vsc::dm::IDataType			*type,
			bool					is_input) :
					TypeField(name, type, false, vsc::dm::TypeFieldAttr::NoAttr),
					m_is_input(is_input) {

}

TypeFieldInOut::~TypeFieldInOut() {
	// TODO Auto-generated destructor stub
}

vsc::dm::IModelField *TypeFieldInOut::mkModelField(
		vsc::dm::IModelBuildContext 		*ctxt,
        const vsc::dm::ValRef               &val) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
	return ctxt_a->mkModelFieldInOut(this);
}

void TypeFieldInOut::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<arl::dm::IVisitor *>(v)) {
		dynamic_cast<arl::dm::IVisitor *>(v)->visitTypeFieldInOut(this);
	}
}

}
}
}
