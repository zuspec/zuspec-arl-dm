
#pragma once
#include "arl/IDataTypeAction.h"
#include "vsc/IDataType.h"
#include "vsc/IModelBuildContext.h"
#include "vsc/IModelField.h"
#include "vsc/IModelFieldFactory.h"
#include "vsc/ITypeField.h"
#include "vsc/impl/TaskIsTypeFieldRef.h"
#include "vsc/impl/TaskBuildModelFieldConstraints.h"
#include "ModelFieldActionRoot.h"
#include "ModelFieldActionType.h"

namespace zsp {
namespace arl {
namespace dm {


class ModelFieldFactoryAction : public virtual vsc::IModelFieldFactory {
public:


    virtual vsc::IModelField *createRootField(
        vsc::IModelBuildContext  *ctxt,
        vsc::IDataType           *type,
        const std::string        &name,
        bool                     is_ref) override {
        vsc::IModelField *ret;

        // Note: Action has no notion of ref
        IDataTypeAction *type_a = dynamic_cast<IDataTypeAction *>(type);
        ret = new ModelFieldActionRoot(name, type_a);

        // Push the new field just for completeness
        ctxt->pushField(ret);
        for (std::vector<vsc::ITypeFieldUP>::const_iterator 
            it=type_a->getFields().begin();
            it!=type_a->getFields().end(); it++) {
            vsc::IModelField *field = (*it)->getDataType()->getFactory()->createTypeField(
                ctxt,
                it->get());
        }
        ctxt->popField();

        // Finally, build out constraints on this field and sub-fields
        vsc::TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
        constraint_builder.build(ret, type);

        return ret;
    }

    virtual vsc::IModelField *createTypeField(
        vsc::IModelBuildContext  *ctxt,
        vsc::ITypeField          *type) override {
        vsc::IModelField *ret = new ModelFieldActionType(type);

        IDataTypeAction *type_a = dynamic_cast<IDataTypeAction *>(type);
        // Push the new field just for completeness
        ctxt->pushField(ret);
        for (std::vector<vsc::ITypeFieldUP>::const_iterator 
            it=type_a->getFields().begin();
            it!=type_a->getFields().end(); it++) {
            vsc::IModelField *field = (*it)->getDataType()->getFactory()->createTypeField(
                ctxt,
                it->get());
        }
        ctxt->popField();

        // Finally, build out constraints on this field and sub-fields
        vsc::TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
        constraint_builder.build(ret, type->getDataType());

        return ret;
    }

};

}
}
}
