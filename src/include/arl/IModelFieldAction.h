/*
 * IModelFieldAction.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelActivity.h"
#include "vsc/IModelField.h"

namespace arl {

class IModelFieldAction;
using IModelFieldActionUP=std::unique_ptr<IModelFieldAction>;
class IModelFieldAction : public virtual vsc::IModelField {
public:

	virtual ~IModelFieldAction() { }

	virtual const std::string &name() const = 0;

	virtual vsc::IDataType *getDataType() const = 0;

	virtual vsc::IModelField *getParent() const = 0;

	virtual void setParent(vsc::IModelField *p) = 0;

	virtual const std::vector<vsc::IModelConstraintUP> &constraints() const = 0;

	virtual void addConstraint(vsc::IModelConstraint *c) = 0;

	virtual const std::vector<vsc::IModelFieldUP> &fields() const = 0;

	virtual void addField(vsc::IModelField *field) = 0;

	virtual vsc::IModelField *getField(int32_t idx) = 0;

	virtual const vsc::IModelVal *val() const = 0;

	virtual vsc::IModelVal *val() = 0;

	virtual vsc::ModelFieldFlag flags() const = 0;

	virtual void clearFlag(vsc::ModelFieldFlag flags) = 0;

	virtual void setFlag(vsc::ModelFieldFlag flags) = 0;

	virtual bool isFlagSet(vsc::ModelFieldFlag flags) const = 0;

	virtual void setFieldData(vsc::IModelFieldData *data) = 0;

	virtual vsc::IModelFieldData *getFieldData() = 0;

	virtual IModelActivity *getActivity() const = 0;

	virtual void setActivity(IModelActivity *a) = 0;

};

}
