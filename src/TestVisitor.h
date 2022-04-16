/*
 * TestVisitor.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "arl/VisitorBase.h"

namespace arl {

class TestVisitor : public VisitorBase {
public:
	TestVisitor();

	virtual ~TestVisitor();

	virtual void visitDataTypeAction(IDataTypeAction *i) override;

};

} /* namespace arl */

