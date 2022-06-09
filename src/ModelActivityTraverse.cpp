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
		vsc::IModelConstraint	*with_c) : m_target(target), m_with_c(with_c) {

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
