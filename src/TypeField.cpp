/*
 * TypeField.cpp
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#include "TypeField.h"
#include "vsc/IDataTypeStruct.h"

namespace arl {

TypeField::TypeField(
		const std::string			&name,
		vsc::IDataType				*type,
		bool						owned,
		vsc::TypeFieldAttr			attr) :
				m_parent(0), m_idx(-1), m_name(name), m_type(type), m_attr(attr) {
	if (owned) {
		m_type_owned = vsc::IDataTypeUP(type);
	}

}

TypeField::~TypeField() {
	// TODO Auto-generated destructor stub
}

vsc::ITypeField *TypeField::getField(int32_t idx) const {
	vsc::IDataTypeStruct *s = dynamic_cast<vsc::IDataTypeStruct *>(getDataType());
	if (s) {
		return s->getField(idx);
	} else {
		return 0;
	}
}

} /* namespace arl */
