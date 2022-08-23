/*
 * DataTypeComponent.cpp
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#include "arl/IContext.h"
#include "vsc/impl/ModelFieldFactoryStruct.h"
#include "vsc/impl/TaskIsTypeFieldRef.h"
#include "vsc/impl/TaskBuildModelFieldConstraints.h"
#include "DataTypeComponent.h"

namespace arl {

DataTypeComponent::DataTypeComponent(const std::string &name) : 
	DataTypeStruct(name, new vsc::ModelFieldFactoryStruct()) {
	// TODO Auto-generated constructor stub

}

DataTypeComponent::~DataTypeComponent() {
	// TODO Auto-generated destructor stub
}

const std::vector<IDataTypeAction *> &DataTypeComponent::getActionTypes() const {
	return m_action_types;
}

void DataTypeComponent::addActionType(IDataTypeAction *action_t) {
	m_action_types.push_back(action_t);
}

void DataTypeComponent::accept(vsc::IVisitor *v) {
	if (dynamic_cast<IVisitor *>(v)) {
		dynamic_cast<IVisitor *>(v)->visitDataTypeComponent(this);
	} else {
		// TODO: abort?
	}
}

vsc::IModelField *DataTypeComponent::createRootField(
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
		vsc::IModelField *activity_f = (*it)->getDataType()->getFactory()->createTypeField(
			ctxt_v,
			*it);
		IModelActivityScope *activity_s = dynamic_cast<IModelActivityScope *>(activity_f);
		ret->addActivity(activity_s);
	}
    ctxt_v->popField();

    // Finally, build out constraints on this field and sub-fields
    vsc::TaskBuildModelFieldConstraints<> constraint_builder(ctxt_v);
    constraint_builder.build(ret, type);

    return ret;	
}

vsc::IModelField *DataTypeComponent::createTypeField(
        vsc::IModelBuildContext  *ctxt,
        vsc::ITypeField          *type) {

    if (vsc::TaskIsTypeFieldRef().eval(type)) {
        return ctxt->ctxt()->mkModelFieldRefType(type);
    } else {
        vsc::IModelField *ret = ctxt->ctxt()->mkModelFieldType(type);

	    vsc::IDataTypeStruct *type_s = dynamic_cast<vsc::IDataTypeStruct *>(type);
	    // Push the new field just for completeness
	    ctxt->pushField(ret);
	    for (std::vector<vsc::ITypeFieldUP>::const_iterator 
	        it=type_s->getFields().begin();
	        it!=type_s->getFields().end(); it++) {
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
}

} /* namespace arl */
