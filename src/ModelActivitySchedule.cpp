/*
 * ModelActivitySchedule.cpp
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#include "arl/IVisitor.h"
#include "ModelActivitySchedule.h"

namespace arl {

ModelActivitySchedule::ModelActivitySchedule(
		const std::string		&name,
		IDataTypeActivity		*type) : 
		ModelActivityScope(ModelActivityScopeT::Schedule),
		m_name(name), m_type(type) {
	// TODO Auto-generated constructor stub

}

ModelActivitySchedule::~ModelActivitySchedule() {
	// TODO Auto-generated destructor stub
}

void ModelActivitySchedule::addActivity(IModelActivity *a, bool own) {
	m_activities.push_back(a);

	if (own) {
		m_activities_up.push_back(IModelActivityUP(a));
	}
}

void ModelActivitySchedule::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelActivitySchedule(this);
	}
}

} /* namespace arl */
