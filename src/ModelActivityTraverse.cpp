/*
 * ModelActivityTraverse.cpp
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#include "arl/IVisitor.h"
#include "ModelActivityTraverse.h"

namespace arl {

ModelActivityTraverse::ModelActivityTraverse(
		IModelFieldAction		*target,
		vsc::IModelConstraint	*with_c,
		bool					own_with_c,
		IModelActivity			*activity,
		bool					owned) : 
		m_target(target), m_with_c(with_c), m_with_c_u(own_with_c?with_c:0),
		m_parent_pool(0), m_activity(activity), m_activity_u(owned?activity:0),
		m_processed(false) {

}

ModelActivityTraverse::~ModelActivityTraverse() {
	// TODO Auto-generated destructor stub
}

void ModelActivityTraverse::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelActivityTraverse(this);
	}
}

} /* namespace arl */
