/*
 * TypeActivitySequence.cpp
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#include "arl/IVisitor.h"
#include "TypeActivitySequence.h"

namespace arl {

TypeActivitySequence::TypeActivitySequence() {
	// TODO Auto-generated constructor stub

}

TypeActivitySequence::~TypeActivitySequence() {
	// TODO Auto-generated destructor stub
}

void TypeActivitySequence::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitTypeActivitySequence(this);
	}
}

} /* namespace arl */
