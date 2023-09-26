/*
 * DataTypeAction.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "DebugMacros.h"
#include "zsp/arl/dm/IContext.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/impl/TaskBuildModelFieldConstraints.h"
#include "DataTypeAction.h"
#include "ModelFieldAction.h"

namespace zsp {
namespace arl {
namespace dm {


DataTypeAction::DataTypeAction(
		IContext			*ctxt,
		const std::string 	&name) : DataTypeArlStruct(name), m_component_t(0) {
//    DEBUG_INIT("DataTypeAction", ctxt->getDebugMgr());

	// Add the built-in 'comp' ref
	m_comp = ctxt->mkTypeFieldRef("comp", 0, vsc::dm::TypeFieldAttr::NoAttr);
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

vsc::dm::IModelField *DataTypeAction::mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			    &name,
		bool						    is_ref) {
    DEBUG_ENTER("mkRootField %s", name.c_str());
    vsc::dm::ValRefStruct val(ctxt->ctxt()->mkValRefStruct(this));
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
    IModelFieldAction *ret;

	ret = ctxt_a->mkModelFieldActionRoot(name, this);

    // Push the new field just for completeness
    ctxt->pushTopDownScope(ret);
    for (uint32_t i=0; i<getFields().size(); i++) {
        vsc::dm::ValRef val_s(val.getFieldRef(i));
        vsc::dm::IModelField *field = getField(i)->mkModelField(ctxt, val_s);

        if (!field) {
            fprintf(stdout, "Error: Construction of field %s failed\n", 
                getField(i)->name().c_str());
        }
		ret->addField(field);
    }

	// Build out any activities
    if (activities().size() == 1) {
        ret->setActivity(dynamic_cast<IModelActivityScope *>(
            activities().at(0)->mkActivity(ctxt)));
    } else if (activities().size() > 1) {
        IModelActivityScope *schedule = ctxt_a->mkModelActivityScope(
            ModelActivityScopeT::Schedule);
    	// Build out any activities
    	for (std::vector<ITypeFieldActivity *>::const_iterator
    		it=activities().begin();
    		it!=activities().end(); it++) {
            IModelActivity *activity = (*it)->mkActivity(ctxt);
    		schedule->addActivity(activity);
    	}
        ret->setActivity(schedule);
    }

    // Finally, build out constraints on this field and sub-fields
    vsc::dm::TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
    constraint_builder.build(ret, this);

    if (getCreateHook()) {
        getCreateHook()->create(ret);
    }
    ctxt->popTopDownScope();

    DEBUG_LEAVE("mkRootField %s", name.c_str());
    return ret;	
}

vsc::dm::IModelField *DataTypeAction::mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type,
        const vsc::dm::ValRef           &val) {
    DEBUG_ENTER("mkTypeField %s", type->name().c_str());
    vsc::dm::ValRefStruct val_s(val);
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());

    IModelFieldAction *ret = ctxt_a->mkModelFieldActionType(type);


    // Push the new field just for completeness
    ctxt->pushTopDownScope(ret);
    for (uint32_t i=0; i<getFields().size(); i++) {
        vsc::dm::ValRef val_f(val_s.getFieldRef(i));
        vsc::dm::IModelField *field = getField(i)->mkModelField(ctxt, val_f);
		ret->addField(field);
    }

    if (activities().size() == 1) {
        ret->setActivity(dynamic_cast<IModelActivityScope *>(
            activities().at(0)->mkActivity(ctxt)));

    } else if (activities().size() > 1) {
        IModelActivityScope *schedule = ctxt_a->mkModelActivityScope(
            ModelActivityScopeT::Schedule);
    	// Build out any activities
    	for (std::vector<ITypeFieldActivity *>::const_iterator
    		it=activities().begin();
    		it!=activities().end(); it++) {
            IModelActivity *activity = (*it)->mkActivity(ctxt);
    		schedule->addActivity(dynamic_cast<IModelActivityScope *>(activity));
    	}
    }

    // Finally, build out constraints on this field and sub-fields
    vsc::dm::TaskBuildModelFieldConstraints<> constraint_builder(ctxt);
    constraint_builder.build(ret, this);

    if (getCreateHook()) {
        getCreateHook()->create(ret);
    }

    ctxt->popTopDownScope();

    DEBUG_LEAVE("mkTypeField %s", type->name().c_str());
    return ret;
}



void DataTypeAction::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<IVisitor *>(v)) {
		dynamic_cast<IVisitor *>(v)->visitDataTypeAction(this);
	} else if (v->cascade()) {
		v->visitDataTypeStruct(this);
	}
}

}
}
}
