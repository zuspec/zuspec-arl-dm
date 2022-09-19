
#pragma once
#include "vsc/IModelField.h"

namespace arl {

class IModelFieldPool : public virtual vsc::IModelField {
public:

    virtual ~IModelFieldPool() { }

    virtual vsc::IDataType *getDataTypePool() const = 0;

    virtual void setDataTypePool(vsc::IDataType *t) = 0;


};

}

