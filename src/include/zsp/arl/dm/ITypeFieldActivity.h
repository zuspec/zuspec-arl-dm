/*
 * ITypeFieldActivity.h
 *
 *  Created on: Jun 17, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/ITypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelActivity;

class ITypeFieldActivity;
using ITypeFieldActivityUP=vsc::dm::UP<ITypeFieldActivity>;
class ITypeFieldActivity : public virtual vsc::dm::ITypeField {
public:

	virtual ~ITypeFieldActivity() { }

	virtual IModelActivity *mkActivity(vsc::dm::IModelBuildContext *ctxt) = 0;

};

}
}
}
