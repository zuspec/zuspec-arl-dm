/*
 * TypeFieldInOut.h
 *
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/ITypeFieldInOut.h"
#include "TypeField.h"

namespace vsc {
	class IModelField;
	class IModelBuildContext;
}

namespace zsp {
namespace arl {
namespace dm {



class TypeFieldInOut : public virtual ITypeFieldInOut, public TypeField {
public:
	TypeFieldInOut(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_input);

	virtual ~TypeFieldInOut();

	virtual bool isInput() const override { return m_is_input; }

	virtual vsc::IModelField *mkModelField(
		vsc::IModelBuildContext 			*ctxt) override;

	virtual void accept(vsc::IVisitor *v) override;

private:
	bool							m_is_input;

};

}
}
}

