/*
 * ModelFieldActionType.h
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#pragma once
#include "ModelFieldAction.h"
#include "vsc/ITypeField.h"

namespace arl {

class ModelFieldActionType : public ModelFieldAction {
public:
	ModelFieldActionType(vsc::ITypeField *type);

	virtual ~ModelFieldActionType();

	virtual const std::string &name() const override { return m_type->name(); }

	virtual vsc::IDataType *getDataType() const override { return m_type->getDataType(); }

private:
	vsc::ITypeField				*m_type;
};

} /* namespace arl */

