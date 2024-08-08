/*
 * IDataTypeActivitySequence.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeActivityScope.h"

namespace zsp {
namespace arl {
namespace dm {

class IDataTypeActivitySequence;
using IDataTypeActivitySequenceUP=vsc::dm::UP<IDataTypeActivitySequence>;
class IDataTypeActivitySequence : public virtual IDataTypeActivityScope {
public:

	virtual ~IDataTypeActivitySequence() { }

};

}
}
}
