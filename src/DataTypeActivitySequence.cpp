/*
 * DataTypeActivitySequence.cpp
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#include "DataTypeActivitySequence.h"
#include "arl/IVisitor.h"

namespace arl {

DataTypeActivitySequence::DataTypeActivitySequence() : DataTypeActivityScope("") {
	// TODO Auto-generated constructor stub

}

DataTypeActivitySequence::~DataTypeActivitySequence() {
	// TODO Auto-generated destructor stub
}

void DataTypeActivitySequence::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitDataTypeActivitySequence(this);
	}
}

} /* namespace arl */
