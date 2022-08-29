/*
 * IContext.h
 *
 *  Created on: Apr 2, 2022
 *      Author: mballance
 */
#pragma once
#include "vsc/IContext.h"
#include "arl/IDataTypeAction.h"
#include "arl/IDataTypeActivitySchedule.h"
#include "arl/IDataTypeActivitySequence.h"
#include "arl/IDataTypeActivityTraverse.h"
#include "arl/IDataTypeAction.h"
#include "arl/IDataTypeComponent.h"
#include "arl/IDataTypeFlowObj.h"
#include "arl/IModelActivityParallel.h"
#include "arl/IModelActivitySchedule.h"
#include "arl/IModelActivitySequence.h"
#include "arl/IModelActivityTraverse.h"
#include "arl/IModelEvaluator.h"
#include "arl/IModelFieldAction.h"
#include "arl/IModelFieldComponent.h"
#include "arl/ITypeFieldClaim.h"
#include "arl/ITypeFieldInOut.h"

namespace arl {

class IContext : public virtual vsc::IContext {
public:

	virtual ~IContext() { }

	virtual IModelFieldAction *buildModelAction(
			IDataTypeAction 	*t,
			const std::string	&name) = 0;

	virtual IModelFieldComponent *buildModelComponent(
			IDataTypeComponent 	*t,
			const std::string	&name) = 0;

	virtual IDataTypeAction *findDataTypeAction(const std::string &name) = 0;

	virtual IDataTypeAction *mkDataTypeAction(const std::string &name) = 0;

	virtual bool addDataTypeAction(IDataTypeAction *t) = 0;

	virtual IDataTypeActivitySchedule *mkDataTypeActivitySchedule() = 0;

	virtual IDataTypeActivitySequence *mkDataTypeActivitySequence() = 0;

	virtual IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
			vsc::ITypeExprFieldRef 		*target,
			vsc::ITypeConstraint		*with_c) = 0;

	virtual IDataTypeComponent *findDataTypeComponent(const std::string &name) = 0;

	virtual IDataTypeComponent *mkDataTypeComponent(const std::string &name) = 0;

	virtual bool addDataTypeComponent(IDataTypeComponent *t) = 0;

	virtual IDataTypeFlowObj *findDataTypeFlowObj(const std::string &name) = 0;

	virtual IDataTypeFlowObj *mkDataTypeFlowObj(
			const std::string 	&name,
			FlowObjKindE		kind) = 0;

	virtual bool addDataTypeFlowObj(IDataTypeFlowObj *t) = 0;

	virtual IModelActivityParallel *mkModelActivityParallel() = 0;

	virtual IModelActivitySchedule *mkModelActivitySchedule() = 0;

	virtual IModelActivitySequence *mkModelActivitySequence() = 0;

	virtual IModelActivityTraverse *mkModelActivityTraverse(
			IModelFieldAction		*target,
			vsc::IModelConstraint	*with_c) = 0;

	virtual IModelEvaluator *mkModelEvaluator() = 0;

	virtual IModelFieldAction *mkModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type) = 0;

	virtual IModelFieldAction *mkModelFieldActionType(
			vsc::ITypeField			*type) = 0;

	virtual IModelFieldComponent *mkModelFieldComponent(
			IDataTypeComponent		*type,
			const std::string		&name) = 0;

	virtual ITypeFieldActivity *mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) = 0;

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
