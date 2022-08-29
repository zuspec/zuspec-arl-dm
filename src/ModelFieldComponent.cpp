/*
 * ModelFieldComponent.cpp
 *
 *  Created on: May 17, 2022
 *      Author: mballance
 */

#include "arl/IVisitor.h"
#include "ModelFieldComponent.h"
#include "TaskBuildComponentMap.h"

namespace arl {

ModelFieldComponent::ModelFieldComponent(
		IContext			*ctxt,
		const std::string	&name,
		vsc::IDataType		*type) :
				ModelField(name, type), m_ctxt(ctxt) {

}

ModelFieldComponent::~ModelFieldComponent() {
	// TODO Auto-generated destructor stub
}

void ModelFieldComponent::initCompTree() {
	m_comp_map = ComponentMapUP(TaskBuildComponentMap().build(this));
}

void ModelFieldComponent::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelFieldComponent(this);
	} else if (v->cascade()) {
		v->visitModelField(this);
	}
}

} /* namespace arl */
