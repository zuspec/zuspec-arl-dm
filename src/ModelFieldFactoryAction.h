
#pragma once
#include "zsp/arl/dm/IDataTypeAction.h"
#include "vsc/dm/IDataType.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/IModelField.h"
#include "vsc/dm/IModelFieldFactory.h"
#include "vsc/dm/ITypeField.h"
#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "vsc/dm/impl/TaskBuildModelFieldConstraints.h"
#include "ModelFieldActionRoot.h"
#include "ModelFieldActionType.h"

namespace zsp {
namespace arl {
namespace dm {


class ModelFieldFactoryAction : public virtual vsc::dm::IModelFieldFactory {
public:


    virtual vsc::dm::IModelField *createRootField(
        vsc::dm::IModelBuildContext  *ctxt,
        vsc::dm::IDataType           *type,
        const std::string        &name,
        bool                     is_ref) override {
        vsc::dm::IModelField *ret;

        // Note: Action has no notion of ref
        IDataTypeAction *type_a = dynamic_cast<IDataTypeAction *>(type);
        ret = new ModelFieldActionRoot(name, type_a);

        // Push the new field just for completeness
        ctxt->pushField(ret);
        for (std::vector<vsc::dm::ITypeFieldUP>::const_iterator 
            it=type_a->getFields().begin();
            it!=type_a->getFields().end(); it++) {
            vsc::dm::IModelField *field = (*it)->getDataType()->getFactory()->createTypeField(
                ctxt,
                it->get());
        }
        ctxt->popField();

        // Finally, build out constraints on this field and sub-fields
        vsc::dm::TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
        constraint_builder.build(ret, type);

        return ret;
    }

    virtual vsc::dm::IModelField *createTypeField(
        vsc::dm::IModelBuildContext  *ctxt,
        vsc::dm::ITypeField          *type) override {
        vsc::dm::IModelField *ret = new ModelFieldActionType(type);

        IDataTypeAction *type_a = dynamic_cast<IDataTypeAction *>(type);
        // Push the new field just for completeness
        ctxt->pushField(ret);
        for (std::vector<vsc::dm::ITypeFieldUP>::const_iterator 
            it=type_a->getFields().begin();
            it!=type_a->getFields().end(); it++) {
            vsc::dm::IModelField *field = (*it)->getDataType()->getFactory()->createTypeField(
                ctxt,
                it->get());
        }
        ctxt->popField();

        // Finally, build out constraints on this field and sub-fields
        vsc::dm::TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
        constraint_builder.build(ret, type->getDataType());

        return ret;
    }

};

}
}
}
