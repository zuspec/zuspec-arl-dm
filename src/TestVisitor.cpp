/*
 * TestVisitor.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "TestVisitor.h"

namespace arl {

TestVisitor::TestVisitor() {
	// TODO Auto-generated constructor stub

}

TestVisitor::~TestVisitor() {
	// TODO Auto-generated destructor stub
}

void TestVisitor::visitDataTypeAction(IDataTypeAction *i) {
	VisitorBase::visitDataTypeAction(i);
}

} /* namespace arl */
