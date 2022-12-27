/*
 * TypeFieldActivity.h
 *
 *  Created on: Jun 17, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeActivity.h"
#include "arl/ITypeFieldActivity.h"
#include "TypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class TypeFieldActivity : public virtual ITypeFieldActivity, public TypeField {
public:
	TypeFieldActivity(
			const std::string			&name,
			IDataTypeActivity			*type,
			bool						owned);

	virtual ~TypeFieldActivity();

	virtual IModelActivity *mkActivity(vsc::IModelBuildContext *ctxt) override;

	virtual void accept(vsc::IVisitor *v) override;

private:

};

}
}
}

