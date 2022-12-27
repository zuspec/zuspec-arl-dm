/*
 * ModelActivityTraverse.cpp
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#include "zsp/arl/dm/IVisitor.h"
#include "ModelActivityTraverse.h"

namespace zsp {
namespace arl {
namespace dm {


ModelActivityTraverse::ModelActivityTraverse(
		IModelFieldAction		*target,
		vsc::dm::IModelConstraint	*with_c,
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

void ModelActivityTraverse::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<arl::dm::IVisitor *>(v)) {
		dynamic_cast<arl::dm::IVisitor *>(v)->visitModelActivityTraverse(this);
	}
}

}
}
}
