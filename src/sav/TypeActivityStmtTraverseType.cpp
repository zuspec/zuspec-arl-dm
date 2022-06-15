/*
 * TypeActivityStmtTraverseType.cpp
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#include "sav/TypeActivityStmtTraverseType.h"

namespace arl {

TypeActivityStmtTraverseType::TypeActivityStmtTraverseType(
		IDataTypeAction				*action_t,
		vsc::ITypeConstraint		*constraint) :
			TypeActivityStmtTraverse(constraint), m_action_t(action_t) {
	// TODO Auto-generated constructor stub

}

TypeActivityStmtTraverseType::~TypeActivityStmtTraverseType() {
	// TODO Auto-generated destructor stub
}

void TypeActivityStmtTraverseType::accept(vsc::IVisitor *v) {
	if (dynamic_cast<IVisitor *>(v)) {
		dynamic_cast<IVisitor *>(v)->visitTypeActivityStmtTraverseType(this);
	}
}

} /* namespace arl */
