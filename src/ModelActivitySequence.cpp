/*
 * ModelActivitySequence.cpp
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#include "arl/IVisitor.h"
#include "ModelActivitySequence.h"

namespace arl {

ModelActivitySequence::ModelActivitySequence(
		const std::string		&name,
		IDataTypeActivity		*type) : m_name(name), m_type(type) {
	// TODO Auto-generated constructor stub

}

ModelActivitySequence::~ModelActivitySequence() {
	// TODO Auto-generated destructor stub
}

void ModelActivitySequence::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitModelActivitySequence(this);
	}

}

} /* namespace arl */
