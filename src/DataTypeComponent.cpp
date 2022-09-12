/*
 * DataTypeComponent.cpp
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#include "arl/IContext.h"
#include "vsc/impl/TaskIsTypeFieldRef.h"
#include "vsc/impl/TaskBuildModelFieldConstraints.h"
#include "DataTypeComponent.h"

namespace arl {

DataTypeComponent::DataTypeComponent(const std::string &name) : DataTypeStruct(name) {
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

vsc::IModelField *DataTypeComponent::mkRootField(
		vsc::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) {
	vsc::IModelField *ret;
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());

	fprintf(stdout, "DataTypeComponent::mkRootField %s %d\n", name.c_str(), is_ref);
	if (is_ref) {
		ret = ctxt_a->mkModelFieldRefRoot(this, name);
	} else {
		ret = ctxt_a->mkModelFieldComponentRoot(this, name);

		// Need to build sub-fields and constraints
	    // Push the new field just for completeness
	    ctxt->pushTopDownScope(ret);
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
	    ctxt->popTopDownScope();
	}


	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

vsc::IModelField *DataTypeComponent::mkTypeField(
		vsc::IModelBuildContext		*ctxt,
		vsc::ITypeField				*type) {
	vsc::IModelField *ret;
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());

	if (vsc::TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
		ret = ctxt_a->mkModelFieldComponentType(type);

	    // Push the new field just for completeness
	    ctxt->pushTopDownScope(ret);
	    for (std::vector<vsc::ITypeFieldUP>::const_iterator 
	        it=getFields().begin();
	        it!=getFields().end(); it++) {
	        vsc::IModelField *field = (*it)->getDataType()->mkTypeField(
	            ctxt,
	            it->get());
			ret->addField(field);
	    }
	    ctxt->popTopDownScope();
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

} /* namespace arl */
