/*
 * ModelFieldActionType.h
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#pragma once
#include "ModelFieldAction.h"
#include "vsc/dm/ITypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class ModelFieldActionType : public ModelFieldAction {
public:
	ModelFieldActionType(vsc::dm::ITypeField *type);

	virtual ~ModelFieldActionType();

	virtual const std::string &name() const override { return m_type->name(); }

	virtual vsc::dm::IDataType *getDataType() const override { return m_type->getDataType(); }

private:
	vsc::dm::ITypeField				*m_type;
};

}
}
}

