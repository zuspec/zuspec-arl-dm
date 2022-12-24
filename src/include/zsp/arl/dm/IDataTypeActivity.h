/*
 * IDataTypeActivity.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "arl/ITypeFieldActivity.h"
#include "vsc/IDataTypeStruct.h"
#include "vsc/IModelBuildContext.h"

namespace arl {

class IModelActivity;

class IDataTypeActivity;
using IDataTypeActivityUP=std::unique_ptr<IDataTypeActivity>;
class IDataTypeActivity : public virtual vsc::IDataType {
public:

	virtual ~IDataTypeActivity() { }

	virtual IModelActivity *mkActivity(
		vsc::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) = 0;


};

}
