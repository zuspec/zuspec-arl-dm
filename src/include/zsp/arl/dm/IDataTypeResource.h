
#pragma once
#include "zsp/arl/dm/IDataTypeFlowObj.h"
#include "vsc/dm/ITypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class IDataTypeResource : public virtual IDataTypeFlowObj {
public:

    virtual ~IDataTypeResource() { }

    virtual vsc::dm::ITypeField *getInstanceId() const = 0;

};

}
}
}
