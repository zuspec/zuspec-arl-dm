/*
 * DataTypeAction.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "arl/IContext.h"
#include "vsc/IModelBuildContext.h"
#include "vsc/impl/TaskBuildModelFieldConstraints.h"
#include "DataTypeAction.h"
#include "ModelFieldAction.h"

namespace arl {

DataTypeAction::DataTypeAction(
		IContext			*ctxt,
		const std::string 	&name) : DataTypeStruct(name, 0), m_component_t(0) {

	// Add the built-in 'comp' ref
	m_comp = ctxt->mkTypeFieldRef("comp", 0, vsc::TypeFieldAttr::NoAttr);
	addField(m_comp);
}

DataTypeAction::~DataTypeAction() {
	// TODO Auto-generated destructor stub
}

void DataTypeAction::setComponentType(IDataTypeComponent *t) {
	m_component_t = t;
    m_comp->setDataType(t);
}

void DataTypeAction::addActivity(ITypeFieldActivity *activity) {
	activity->setIndex(m_activities.size());
	m_activities.push_back(activity);
}

vsc::IModelField *DataTypeAction::createRootField(
    vsc::IModelBuildContext  *ctxt_v,
    vsc::IDataType           *type,
    const std::string   	 &name,
    bool                is_ref) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt_v->ctxt());
    IModelFieldAction *ret;

	IDataTypeAction *type_a = dynamic_cast<IDataTypeAction *>(type);
	ret = ctxt_a->mkModelFieldActionRoot(name, type_a);

    // Push the new field just for completeness
    ctxt_v->pushField(ret);
    for (std::vector<vsc::ITypeFieldUP>::const_iterator 
        it=type_a->getFields().begin();
        it!=type_a->getFields().end(); it++) {
        vsc::IModelField *field = (*it)->getDataType()->getFactory()->createTypeField(
            ctxt_v,
            it->get());
		ret->addField(field);
    }
    ctxt_v->popField();

	// Build out any activities
    ctxt_v->pushField(ret);
	for (std::vector<ITypeFieldActivity *>::const_iterator
		it=type_a->activities().begin();
		it!=type_a->activities().end(); it++) {
        IModelActivity *activity = (*it)->mkActivity(ctxt_v);
		ret->addActivity(dynamic_cast<IModelActivityScope *>(activity));
	}
    ctxt_v->popField();

    // Finally, build out constraints on this field and sub-fields
    vsc::TaskBuildModelFieldConstraints<> constraint_builder(ctxt_v);
    constraint_builder.build(ret, type);

    return ret;	
}

vsc::IModelField *DataTypeAction::createTypeField(
        vsc::IModelBuildContext  *ctxt,
        vsc::ITypeField          *type) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
	IDataTypeAction *type_a = dynamic_cast<IDataTypeAction *>(type->getDataType());

    IModelFieldAction *ret = ctxt_a->mkModelFieldActionType(type);


    // Push the new field just for completeness
    ctxt->pushField(ret);
    for (std::vector<vsc::ITypeFieldUP>::const_iterator 
        it=type_a->getFields().begin();
        it!=type_a->getFields().end(); it++) {
        vsc::IModelField *field = (*it)->getDataType()->getFactory()->createTypeField(
            ctxt,
            it->get());
		ret->addField(field);
    }
    ctxt->popField();

    // Finally, build out constraints on this field and sub-fields
    vsc::TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
    constraint_builder.build(ret, type_a);

    if (type_a->getCreateHook()) {
        type_a->getCreateHook()->create(ret);
    }

    return ret;
}

void DataTypeAction::accept(vsc::IVisitor *v) {
	if (dynamic_cast<IVisitor *>(v)) {
		dynamic_cast<IVisitor *>(v)->visitDataTypeAction(this);
	} else {
		// TODO:
	}
}

} /* namespace arl */
