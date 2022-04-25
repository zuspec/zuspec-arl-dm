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

namespace arl {

class IContext : public vsc::IContext {
public:

	virtual ~IContext() { }

	virtual vsc::IModelField *buildModelComponent(IDataTypeComponent *t) = 0;

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

};

}
