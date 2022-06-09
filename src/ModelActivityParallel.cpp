/*
 * ModelActivityParallel.cpp
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#include "arl/IVisitor.h"
#include "ModelActivityParallel.h"

namespace arl {

ModelActivityParallel::ModelActivityParallel() {
	// TODO Auto-generated constructor stub

}

ModelActivityParallel::~ModelActivityParallel() {
	// TODO Auto-generated destructor stub
}

void ModelActivityParallel::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelActivityParallel(this);
	}
}

} /* namespace arl */
