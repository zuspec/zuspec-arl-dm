/*
 * ModelActivityParallel.cpp
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#include "arl/IVisitor.h"
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

void ModelActivityParallel::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelActivityParallel(this);
	}
}

}
}
}
