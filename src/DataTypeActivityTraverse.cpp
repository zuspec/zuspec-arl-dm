/*
 * DataTypeActivityTraverse.cpp
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#include "DataTypeActivityTraverse.h"
#include "arl/IVisitor.h"

namespace arl {

DataTypeActivityTraverse::DataTypeActivityTraverse(
		vsc::ITypeExprFieldRef 		*target,
		vsc::ITypeConstraint		*with_c) : m_target(target), m_with_c(with_c) {
	// TODO Auto-generated constructor stub

}

DataTypeActivityTraverse::~DataTypeActivityTraverse() {
	// TODO Auto-generated destructor stub
}

void DataTypeActivityTraverse::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitDataTypeActivityTraverse(this);
	}
}

} /* namespace arl */
