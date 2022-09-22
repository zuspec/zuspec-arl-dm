
#pragma once
#include <vector>
#include "vsc/IModelField.h"

namespace arl {

class IModelFieldPool : public virtual vsc::IModelField {
public:

    virtual ~IModelFieldPool() { }

    virtual vsc::IDataType *getDataTypePool() const = 0;

    virtual void setDataTypePool(vsc::IDataType *t) = 0;

    virtual void addObject(vsc::IModelField *obj) = 0;

    virtual const std::vector<vsc::IModelFieldUP> &getObjects() const = 0;


};

}

