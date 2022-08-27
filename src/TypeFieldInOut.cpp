/*
 * TypeFieldInOut.cpp
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#include "arl/IVisitor.h"
#include "TypeFieldInOut.h"

namespace arl {

TypeFieldInOut::TypeFieldInOut(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_input) :
					TypeField(name, type, false, vsc::TypeFieldAttr::NoAttr),
					m_is_input(is_input) {

}

TypeFieldInOut::~TypeFieldInOut() {
	// TODO Auto-generated destructor stub
}

void TypeFieldInOut::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitTypeFieldInOut(this);
	}
}

} /* namespace arl */
