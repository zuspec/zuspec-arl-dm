/*
 * ITypeActivitySequence.h
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/ITypeActivityStmt.h"

namespace arl {

class ITypeActivitySequence;
using ITypeActivitySequenceUP=std::unique_ptr<ITypeActivitySequence>;
class ITypeActivitySequence : public ITypeActivityStmt {
public:

	virtual ~ITypeActivitySequence() { }

};

}
