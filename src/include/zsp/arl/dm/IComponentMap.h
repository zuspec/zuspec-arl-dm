
#pragma once
#include <vector>
#include "zsp/arl/dm/IDataTypeComponent.h"
#include "zsp/arl/dm/IModelFieldPool.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelFieldComponent;

class IComponentMap {
public:

    virtual ~IComponentMap() { }

    virtual void addSubComponentMap(const IComponentMap *m) = 0;

    /**
     * @brief Return all legal sub-contexts for the specified component type
     */
    virtual const std::vector<IModelFieldComponent *> &getSubContexts(IDataTypeComponent *t) const = 0;

    virtual const std::vector<IDataTypeComponent *> &getComponentTypes() const = 0;

    virtual void addPoolMapping(vsc::dm::ITypeField *claim_ref, IModelFieldPool *pool) = 0;

    /**
     * @brief Returns the pool mapped to the specified claim field in this context
     * 
     */
    virtual IModelFieldPool *getPool(vsc::dm::ITypeField *claim_ref) const = 0;


};

}
}
}
