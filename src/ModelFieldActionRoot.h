/*
 * ModelFieldActionRoot.h
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#pragma once
#include "ModelFieldAction.h"
#include "arl/IDataTypeAction.h"

namespace arl {

class ModelFieldActionRoot : public ModelFieldAction {
public:
	ModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type);

	virtual ~ModelFieldActionRoot();

	virtual const std::string &name() const override {
		return m_name;
	}

	virtual vsc::IDataType *getDataType() const override {
		return m_type;
	}

private:
	std::string								m_name;
	IDataTypeAction							*m_type;

};

} /* namespace arl */

