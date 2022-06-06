/*
 * ModelActivityTraverse.cpp
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#include "ModelActivityTraverse.h"

namespace arl {

ModelActivityTraverse::ModelActivityTraverse(
		IModelFieldAction		*target,
		vsc::IModelConstraint	*with_c) : m_target(target), m_with_c(with_c) {

}

ModelActivityTraverse::~ModelActivityTraverse() {
	// TODO Auto-generated destructor stub
}

} /* namespace arl */
