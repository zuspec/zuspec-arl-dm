/*
 * ModelFieldAction.cpp
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#include "ModelFieldAction.h"
#include "zsp/arl/dm/IVisitor.h"

namespace zsp {
namespace arl {
namespace dm {


ModelFieldAction::ModelFieldAction() {

}

ModelFieldAction::~ModelFieldAction() {
	// TODO Auto-generated destructor stub
}

void ModelFieldAction::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<arl::dm::IVisitor *>(v)) {
		dynamic_cast<arl::dm::IVisitor *>(v)->visitModelFieldAction(this);
	} else if (v->cascade()) {
		v->visitModelField(this);
	}
}

}
}
}
