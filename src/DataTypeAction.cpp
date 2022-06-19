/*
 * DataTypeAction.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "DataTypeAction.h"

namespace arl {

DataTypeAction::DataTypeAction(
		IContext			*ctxt,
		const std::string 	&name) : DataTypeStruct(name), m_component_t(0) {

	// Add the built-in 'comp' ref
	addField(ctxt->mkTypeFieldRef("comp", 0, vsc::TypeFieldAttr::NoAttr));
}

DataTypeAction::~DataTypeAction() {
	// TODO Auto-generated destructor stub
}

void DataTypeAction::setComponentType(IDataTypeComponent *t) {
	m_component_t = t;
}

void DataTypeAction::addActivity(ITypeFieldActivity *activity) {
	activity->setIndex(m_fields.size());
	m_fields.push_back(vsc::ITypeFieldUP(activity));
	m_activities.push_back(activity);
}

void DataTypeAction::accept(vsc::IVisitor *v) {
	if (dynamic_cast<IVisitor *>(v)) {
		dynamic_cast<IVisitor *>(v)->visitDataTypeAction(this);
	} else {
		// TODO:
	}
}

} /* namespace arl */
