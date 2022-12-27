
#pragma once
#include "zsp/arl/dm/impl/VisitorBase.h"
#include "vsc/dm/impl/ModelFieldFactoryStruct.h"

namespace zsp {
namespace arl {
namespace dm {


class ModelFieldFactory : 
    public virtual VisitorBase,
    public virtual vsc::dm::ModelFieldFactoryStruct {
public:
}

}