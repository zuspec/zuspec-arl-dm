
#pragma once
#include "arl/impl/VisitorBase.h"
#include "vsc/impl/ModelFieldFactoryStruct.h"

namespace arl {

class ModelFieldFactory : 
    public virtual VisitorBase,
    public virtual vsc::ModelFieldFactoryStruct {
public:
}

}