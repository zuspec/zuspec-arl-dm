/*
 * IDataTypeActivity.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "zsp/arl/dm/ITypeFieldActivity.h"
#include "vsc/dm/IDataTypeStruct.h"
#include "vsc/dm/IModelBuildContext.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelActivity;

class IDataTypeActivity;
using IDataTypeActivityUP=std::unique_ptr<IDataTypeActivity>;
class IDataTypeActivity : public virtual vsc::dm::IDataType {
public:

	virtual ~IDataTypeActivity() { }

	virtual IModelActivity *mkActivity(
		vsc::dm::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) = 0;


};

}
}
}
