/*
 * ITypeFieldActivity.h
 *
 *  Created on: Jun 17, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/ITypeField.h"

namespace arl {

class ITypeFieldActivity;
using ITypeFieldActivityUP=std::unique_ptr<ITypeFieldActivity>;
class ITypeFieldActivity : public virtual vsc::ITypeField {
public:

	virtual ~ITypeFieldActivity() { }


};


}
