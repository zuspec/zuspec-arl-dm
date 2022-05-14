/*
 * TypeFieldInOut.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/ITypeFieldInOut.h"
#include "TypeField.h"

namespace arl {

class TypeFieldInOut : public virtual ITypeFieldInOut, public TypeField {
public:
	TypeFieldInOut(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_input);

	virtual ~TypeFieldInOut();

	virtual bool isInput() const override { return m_is_input; }

	virtual void accept(vsc::IVisitor *v) override;

private:
	bool							m_is_input;

};

} /* namespace arl */

