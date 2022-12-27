
#pragma once
#include "arl/IDataTypeFlowObj.h"
#include "vsc/ITypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeResource : public virtual IDataTypeFlowObj {
public:

    virtual ~IDataTypeResource() { }

    virtual vsc::ITypeField *getInstanceId() const = 0;

};

}
}
}
