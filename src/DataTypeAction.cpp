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
		const std::string 	&name) : DataTypeStruct(name), m_component_t(0) {

	// Add the built-in 'comp' ref
    /*
	m_comp = ctxt->mkTypeFieldRef("comp", 0, vsc::TypeFieldAttr::NoAttr);
	addField(m_comp);
     */
}

DataTypeAction::~DataTypeAction() {
	// TODO Auto-generated destructor stub
}

void DataTypeAction::setComponentType(IDataTypeComponent *t) {
	m_component_t = t;
//    m_comp->setDataType(t);
}

void DataTypeAction::addActivity(ITypeFieldActivity *activity) {
	activity->setIndex(m_activities.size());
	m_activities.push_back(activity);
}

vsc::IModelField *DataTypeAction::mkRootField(
		vsc::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
    IModelFieldAction *ret;

	ret = ctxt_a->mkModelFieldActionRoot(name, this);

    // Push the new field just for completeness
    ctxt->pushField(ret);
    for (std::vector<vsc::ITypeFieldUP>::const_iterator 
        it=getFields().begin();
        it!=getFields().end(); it++) {
        vsc::IModelField *field = (*it)->getDataType()->mkTypeField(
            ctxt,
            it->get());
        if (!field) {
            fprintf(stdout, "Error: Construction of field %s failed\n", (*it)->name().c_str());
        }
		ret->addField(field);
    }
    ctxt->popField();

	// Build out any activities
    ctxt->pushField(ret);
	for (std::vector<ITypeFieldActivity *>::const_iterator
		it=activities().begin();
		it!=activities().end(); it++) {
        IModelActivity *activity = (*it)->mkActivity(ctxt);
		ret->addActivity(dynamic_cast<IModelActivityScope *>(activity));
	}
    ctxt->popField();

    // Finally, build out constraints on this field and sub-fields
    vsc::TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
    constraint_builder.build(ret, this);

    if (getCreateHook()) {
        getCreateHook()->create(ret);
    }

    return ret;	
}

vsc::IModelField *DataTypeAction::mkTypeField(
		vsc::IModelBuildContext		*ctxt,
		vsc::ITypeField				*type) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());

    IModelFieldAction *ret = ctxt_a->mkModelFieldActionType(type);


    // Push the new field just for completeness
    ctxt->pushField(ret);
    for (std::vector<vsc::ITypeFieldUP>::const_iterator 
        it=getFields().begin();
        it!=getFields().end(); it++) {
        vsc::IModelField *field = (*it)->getDataType()->mkTypeField(
            ctxt,
            it->get());
		ret->addField(field);
    }
    ctxt->popField();

    // Finally, build out constraints on this field and sub-fields
    vsc::TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
    constraint_builder.build(ret, this);

    if (getCreateHook()) {
        getCreateHook()->create(ret);
    }

    return ret;
}

void DataTypeAction::accept(vsc::IVisitor *v) {
	if (dynamic_cast<IVisitor *>(v)) {
		dynamic_cast<IVisitor *>(v)->visitDataTypeAction(this);
	} else if (v->cascade()) {
		v->visitDataTypeStruct(this);
	}
}

} /* namespace arl */
