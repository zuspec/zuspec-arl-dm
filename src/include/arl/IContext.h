/*
 * IContext.h
 *
 *  Created on: Apr 2, 2022
 *      Author: mballance
 */
#pragma once
#include "vsc/IContext.h"
#include "arl/IDataTypeAction.h"
#include "arl/IDataTypeComponent.h"
#include "arl/IDataTypeFlowObj.h"
#include "arl/IModelEvaluator.h"
#include "arl/ITypeActivityStmtTraverseType.h"
#include "arl/ITypeFieldClaim.h"
#include "arl/ITypeFieldInOut.h"

namespace arl {

class IContext : public virtual vsc::IContext {
public:

	virtual ~IContext() { }

	virtual vsc::IModelField *buildModelAction(
			IDataTypeAction 	*t,
			const std::string	&name) = 0;

	virtual vsc::IModelField *buildModelComponent(
			IDataTypeComponent 	*t,
			const std::string	&name) = 0;

	virtual IDataTypeAction *findDataTypeAction(const std::string &name) = 0;

	virtual IDataTypeAction *mkDataTypeAction(const std::string &name) = 0;

	virtual bool addDataTypeAction(IDataTypeAction *t) = 0;

	virtual IDataTypeComponent *findDataTypeComponent(const std::string &name) = 0;

	virtual IDataTypeComponent *mkDataTypeComponent(const std::string &name) = 0;

	virtual bool addDataTypeComponent(IDataTypeComponent *t) = 0;

	virtual IDataTypeFlowObj *findDataTypeFlowObj(const std::string &name) = 0;

	virtual IDataTypeFlowObj *mkDataTypeFlowObj(
			const std::string 	&name,
			FlowObjKindE		kind) = 0;

	virtual bool addDataTypeFlowObj(IDataTypeFlowObj *t) = 0;

	virtual IModelEvaluator *mkModelEvaluator() = 0;

	virtual ITypeActivityStmtTraverseType *mkTypeActivityStmtTraverseType(
			IDataTypeAction			*action_t,
			vsc::ITypeConstraint	*constraint) = 0;

	virtual ITypeFieldClaim *mkTypeFieldClaim(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_lock) = 0;

	virtual ITypeFieldInOut *mkTypeFieldInOut(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_input) = 0;

	virtual ITypeFieldPool *mkTypeFieldPool(
			const std::string		&name,
			vsc::IDataType			*type,
			vsc::TypeFieldAttr		attr,
			int32_t					decl_size) = 0;

};

}
