/*
 * Context.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <unordered_map>
#include "arl/IContext.h"
#include "vsc/impl/ContextDelegator.h"

namespace arl {

class Context : public virtual arl::IContext, public vsc::ContextDelegator {
public:
	Context(vsc::IContext *ctxt);

	virtual ~Context();

	virtual IModelFieldAction *buildModelAction(
			IDataTypeAction 	*t,
			const std::string	&name) override;

	virtual IModelFieldComponent *buildModelComponent(
			IDataTypeComponent 	*t,
			const std::string	&name) override;

	virtual IDataTypeAction *findDataTypeAction(const std::string &) override;

	virtual IDataTypeAction *mkDataTypeAction(const std::string &name) override;

	virtual bool addDataTypeAction(IDataTypeAction *t) override;

	virtual IDataTypeActivitySchedule *mkDataTypeActivitySchedule() override;

	virtual IDataTypeActivitySequence *mkDataTypeActivitySequence() override;

	virtual IDataTypeActivityTraverse *mkDataTypeActivityTraverse(
			vsc::ITypeExprFieldRef	*target,
			vsc::ITypeConstraint	*with_c) override;

	virtual IDataTypeComponent *findDataTypeComponent(const std::string &name) override;

	virtual IDataTypeComponent *mkDataTypeComponent(const std::string &name) override;

	virtual bool addDataTypeComponent(IDataTypeComponent *t) override;

	virtual IDataTypeFlowObj *findDataTypeFlowObj(const std::string &name) override;

	virtual IDataTypeFlowObj *mkDataTypeFlowObj(
			const std::string 	&name,
			FlowObjKindE		kind) override;

	virtual bool addDataTypeFlowObj(IDataTypeFlowObj *t) override;

	virtual IModelActivityParallel *mkModelActivityParallel() override;

	virtual IModelActivitySchedule *mkModelActivitySchedule() override;

	virtual IModelActivitySequence *mkModelActivitySequence() override;

	virtual IModelActivityTraverse *mkModelActivityTraverse(
			IModelFieldAction		*target,
			vsc::IModelConstraint	*with_c) override;

	virtual IModelEvaluator *mkModelEvaluator() override;

	virtual IModelFieldAction *mkModelFieldActionRoot(
			const std::string		&name,
			IDataTypeAction			*type) override;

	virtual IModelFieldAction *mkModelFieldActionType(
			vsc::ITypeField			*type) override;

	virtual IModelFieldComponent *mkModelFieldComponent(
			IDataTypeComponent		*type,
			const std::string		&name) override;

	virtual ITypeFieldActivity *mkTypeFieldActivity(
			const std::string		&name,
			IDataTypeActivity		*type,
			bool					owned) override;

	virtual ITypeFieldClaim *mkTypeFieldClaim(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_lock) override;

	virtual ITypeFieldInOut *mkTypeFieldInOut(
			const std::string		&name,
			vsc::IDataType			*type,
			bool					is_input) override;

	virtual ITypeFieldPool *mkTypeFieldPool(
			const std::string		&name,
			vsc::IDataType			*type,
			vsc::TypeFieldAttr		attr,
			int32_t					decl_size) override;

private:
	std::unordered_map<std::string, IDataTypeActionUP>			m_action_type_m;
	std::unordered_map<std::string, IDataTypeComponentUP>		m_component_type_m;
	std::unordered_map<std::string, IDataTypeFlowObjUP>			m_flowobj_type_m;

};

} /* namespace arl */

