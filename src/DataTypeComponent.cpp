/*
 * DataTypeComponent.cpp
 *
 *  Created on: Apr 24, 2022
 *      Author: mballance
 */

#include "zsp/arl/dm/IContext.h"
#include "vsc/dm/impl/TaskIsTypeFieldRef.h"
#include "vsc/dm/impl/TaskBuildModelFieldConstraints.h"
#include "DataTypeComponent.h"

namespace zsp {
namespace arl {
namespace dm {


DataTypeComponent::DataTypeComponent(
	IContext			*ctxt,
	const std::string 	&name) : DataTypeArlStruct(name) {

	// Could back-patch this once we know the number of 
	// instances
	vsc::dm::IDataTypeInt *ui32 = ctxt->findDataTypeInt(false, 32);

	if (!ui32) {
		ui32 = ctxt->mkDataTypeInt(false, 32);
		ctxt->addDataTypeInt(ui32);
	}

	m_comp_id = ctxt->mkTypeFieldPhy(
		"comp_id", 
		ui32, 
		false, 
		vsc::dm::TypeFieldAttr::Rand,
		0, false);
	addField(m_comp_id);
}

DataTypeComponent::~DataTypeComponent() {
	// TODO Auto-generated destructor stub
}

const std::vector<IDataTypeAction *> &DataTypeComponent::getActionTypes() const {
	return m_action_types;
}

void DataTypeComponent::addActionType(IDataTypeAction *action_t) {
    action_t->setComponentType(this);
	m_action_types.push_back(action_t);
}

void DataTypeComponent::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<IVisitor *>(v)) {
		dynamic_cast<IVisitor *>(v)->visitDataTypeComponent(this);
	} else {
		// TODO: abort?
	}
}

vsc::dm::IModelField *DataTypeComponent::mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) {
	vsc::dm::IModelField *ret;
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());

	if (is_ref) {
		ret = ctxt_a->mkModelFieldRefRoot(this, name);
	} else {
		ret = ctxt_a->mkModelFieldComponentRoot(this, name);

		// Need to build sub-fields and constraints
	    // Push the new field just for completeness
	    ctxt->pushTopDownScope(ret);
	    for (std::vector<vsc::dm::ITypeFieldUP>::const_iterator 
	        it=getFields().begin();
	        it!=getFields().end(); it++) {
	        vsc::dm::IModelField *field = (*it)->mkModelField(ctxt);
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

vsc::dm::IModelField *DataTypeComponent::mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type) {
	vsc::dm::IModelField *ret;
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());

	if (vsc::dm::TaskIsTypeFieldRef().eval(type)) {
		ret = ctxt->ctxt()->mkModelFieldRefType(type);
	} else {
		ret = ctxt_a->mkModelFieldComponentType(type);

	    // Push the new field just for completeness
	    ctxt->pushTopDownScope(ret);
	    for (std::vector<vsc::dm::ITypeFieldUP>::const_iterator 
	        it=getFields().begin();
	        it!=getFields().end(); it++) {
	        vsc::dm::IModelField *field = (*it)->mkModelField(ctxt);
			ret->addField(field);
	    }
	    ctxt->popTopDownScope();
	}

	if (getCreateHook()) {
		getCreateHook()->create(ret);
	}

	return ret;
}

}
}
}
