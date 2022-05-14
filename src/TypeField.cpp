/*
 * TypeField.cpp
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#include "TypeField.h"

namespace arl {

TypeField::TypeField(
		const std::string			&name,
		vsc::IDataType				*type,
		vsc::TypeFieldAttr			attr) :
				m_parent(0), m_name(name), m_type(type), m_attr(attr) {

}

TypeField::~TypeField() {
	// TODO Auto-generated destructor stub
}

} /* namespace arl */
