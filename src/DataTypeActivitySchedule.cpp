/*
 * DataTypeActivitySchedule.cpp
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#include "DataTypeActivitySchedule.h"
#include "arl/IVisitor.h"

namespace arl {

DataTypeActivitySchedule::DataTypeActivitySchedule() : DataTypeActivityScope("") {
	// TODO Auto-generated constructor stub

}

DataTypeActivitySchedule::~DataTypeActivitySchedule() {
	// TODO Auto-generated destructor stub
}

void DataTypeActivitySchedule::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitDataTypeActivitySchedule(this);
	}
}

} /* namespace arl */
