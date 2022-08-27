/*
 * TypeFieldPool.cpp
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#include "TypeFieldPool.h"
#include "arl/IVisitor.h"

namespace arl {

TypeFieldPool::TypeFieldPool(
		const std::string			&name,
		vsc::IDataType				*type,
		vsc::TypeFieldAttr			attr,
		int32_t						decl_size) :
				TypeField(name, type, false, attr), m_decl_size(decl_size) {

}

TypeFieldPool::~TypeFieldPool() {
	// TODO Auto-generated destructor stub
}

void TypeFieldPool::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitTypeFieldPool(this);
	}
}

} /* namespace arl */
