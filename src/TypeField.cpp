/*
 * TypeField.cpp
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#include "TypeField.h"
#include "vsc/dm/IDataTypeStruct.h"

namespace zsp {
namespace arl {
namespace dm {


TypeField::TypeField(
		const std::string			&name,
		vsc::dm::IDataType			*type,
		bool						owned,
		vsc::dm::TypeFieldAttr		attr) :
				m_parent(0), m_idx(-1), m_name(name), 
                m_offset(-1), m_type(type, owned), m_attr(attr) {
}

TypeField::~TypeField() {
	// TODO Auto-generated destructor stub
}

vsc::dm::ITypeField *TypeField::getField(int32_t idx) const {
	vsc::dm::IDataTypeStruct *s = dynamic_cast<vsc::dm::IDataTypeStruct *>(getDataType());
	if (s) {
		return s->getField(idx);
	} else {
		return 0;
	}
}

vsc::dm::IModelField *TypeField::mkModelField(
		vsc::dm::IModelBuildContext 			*ctxt) {
	return getDataType()->mkTypeField(ctxt, this);
}

}
}
}
