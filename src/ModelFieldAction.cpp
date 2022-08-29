/*
 * ModelFieldAction.cpp
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#include "ModelFieldAction.h"
#include "arl/IVisitor.h"

namespace arl {

ModelFieldAction::ModelFieldAction() {

}

ModelFieldAction::~ModelFieldAction() {
	// TODO Auto-generated destructor stub
}

void ModelFieldAction::addActivity(IModelActivityScope *a) {
	a->setParent(this);
	m_fields.push_back(vsc::IModelFieldUP(a));
	m_activities.push_back(a);
}


void ModelFieldAction::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelFieldAction(this);
	} else if (v->cascade()) {
		v->visitModelField(this);
	}
}

} /* namespace arl */
