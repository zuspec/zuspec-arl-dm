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
	m_flags = vsc::ModelFieldFlag::NoFlags;

}

ModelFieldAction::~ModelFieldAction() {
	// TODO Auto-generated destructor stub
}

void ModelFieldAction::addConstraint(vsc::IModelConstraint *c) {
	m_constraints.push_back(vsc::IModelConstraintUP(c));
}

void ModelFieldAction::addField(vsc::IModelField *field) {
	m_fields.push_back(vsc::IModelFieldUP(field));
}

void ModelFieldAction::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelFieldAction(this);
	} else {
		v->visitModelField(this);
	}
}

} /* namespace arl */
