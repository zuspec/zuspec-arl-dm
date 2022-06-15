/*
 * ITypeActivityStmt.h
 *
 *  Created on: Apr 30, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "vsc/IAccept.h"

namespace arl {

class ITypeActivityStmt;
using ITypeActivityStmtUP=std::unique_ptr<ITypeActivityStmt>;
class ITypeActivityStmt : public vsc::IAccept {
public:


};

}
