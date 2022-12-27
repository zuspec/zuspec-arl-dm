/*
 * ModelFieldActionRoot.h
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#pragma once
#include "ModelFieldAction.h"
#include "zsp/arl/dm/IDataTypeAction.h"

namespace zsp {
namespace arl {
namespace dm {


class ModelFieldActionRoot : public ModelFieldAction {
public:
	ModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type);

	virtual ~ModelFieldActionRoot();

	virtual const std::string &name() const override {
		return m_name;
	}

	virtual vsc::dm::IDataType *getDataType() const override {
		return m_type;
	}

	virtual void setDataType(vsc::dm::IDataType *t) override { 
		m_type = dynamic_cast<IDataTypeAction *>(t); 
	}

private:
	std::string								m_name;
	IDataTypeAction							*m_type;

};

}
}
}

