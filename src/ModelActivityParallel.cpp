/*
 * ModelActivityParallel.cpp
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#include "zsp/arl/dm/IVisitor.h"
#include "ModelActivityParallel.h"

namespace zsp {
namespace arl {
namespace dm {


ModelActivityParallel::ModelActivityParallel() : 
	ModelActivityScope(ModelActivityScopeT::Parallel) {
	// TODO Auto-generated constructor stub

}

ModelActivityParallel::~ModelActivityParallel() {
	// TODO Auto-generated destructor stub
}

void ModelActivityParallel::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<arl::dm::IVisitor *>(v)) {
		dynamic_cast<arl::dm::IVisitor *>(v)->visitModelActivityParallel(this);
	}
}

}
}
}
