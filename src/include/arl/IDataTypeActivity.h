/*
 * IDataTypeActivity.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IDataTypeStruct.h"

namespace arl {

class IDataTypeActivity;
using IDataTypeActivityUP=std::unique_ptr<IDataTypeActivity>;
class IDataTypeActivity : public virtual vsc::IDataType {
public:

	virtual ~IDataTypeActivity() { }

};

}
