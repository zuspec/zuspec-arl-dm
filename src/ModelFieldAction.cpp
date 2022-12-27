/*
 * ModelFieldAction.cpp
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#include "ModelFieldAction.h"
#include "arl/IVisitor.h"

namespace zsp {
namespace arl {
namespace dm {


ModelFieldAction::ModelFieldAction() {

}

ModelFieldAction::~ModelFieldAction() {
	// TODO Auto-generated destructor stub
}

void ModelFieldAction::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelFieldAction(this);
	} else if (v->cascade()) {
		v->visitModelField(this);
	}
}

}
}
}
