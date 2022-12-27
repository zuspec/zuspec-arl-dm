
#pragma once
#include <vector>
#include "vsc/dm/IModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelFieldPool : public virtual vsc::dm::IModelField {
public:

    virtual ~IModelFieldPool() { }

    virtual vsc::dm::IDataType *getDataTypePool() const = 0;

    virtual void setDataTypePool(vsc::dm::IDataType *t) = 0;

    virtual int32_t getId() const = 0;

    virtual void setId(int32_t id) = 0;

    virtual void addObject(vsc::dm::IModelField *obj) = 0;

    virtual const std::pair<int32_t,int32_t> &getGlobalPoolRange() const = 0;

    virtual void setGlobalPoolRange(int32_t i1, int32_t i2) = 0;

    virtual const std::vector<vsc::dm::IModelFieldUP> &getObjects() const = 0;


};

}
}
}

