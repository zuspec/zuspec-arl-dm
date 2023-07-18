/*
 * TypeFieldActivity.h
 *
 *  Created on: Jun 17, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeActivity.h"
#include "zsp/arl/dm/ITypeFieldActivity.h"
#include "TypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class TypeFieldActivity : 
    public virtual ITypeFieldActivity, 
    public virtual TypeField {
public:
	TypeFieldActivity(
			const std::string			&name,
			IDataTypeActivity			*type,
			bool						owned);

	virtual ~TypeFieldActivity();

	virtual IModelActivity *mkActivity(vsc::dm::IModelBuildContext *ctxt) override;

	virtual void accept(vsc::dm::IVisitor *v) override;

private:

};

}
}
}

