
#pragma once
#include <vector>
#include "arl/IDataTypeComponent.h"
#include "arl/IModelFieldPool.h"

namespace arl {

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

    virtual void addPoolMapping(vsc::ITypeField *claim_ref, IModelFieldPool *pool) = 0;

    /**
     * @brief Returns the pool mapped to the specified claim field in this context
     * 
     */
    virtual IModelFieldPool *getPool(vsc::ITypeField *claim_ref) const = 0;


};

}