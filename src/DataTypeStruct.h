/*
 * DataTypeStruct.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <string>
#include <vector>
#include "vsc/dm/IContext.h"
#include "vsc/dm/IDataTypeStruct.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/IModelStructCreateHook.h"
#include "vsc/dm/ITypeField.h"
#include "vsc/dm/ITypeConstraint.h"

namespace zsp {
namespace arl {
namespace dm {


class DataTypeStruct : public virtual vsc::dm::IDataTypeStruct {
public:
	DataTypeStruct(const std::string &name);

	virtual ~DataTypeStruct();

	virtual const std::string &name() const {
		return m_name;
	}

	virtual void addField(
        vsc::dm::ITypeField     *f,
        bool                    owned=true);

	virtual const std::vector<vsc::dm::ITypeFieldUP> &getFields() const;

	virtual vsc::dm::ITypeField *getField(int32_t idx);

	virtual void addConstraint(
        vsc::dm::ITypeConstraint    *c,
        bool                        owned);

	virtual const std::vector<vsc::dm::ITypeConstraintUP> &getConstraints() const;

	virtual vsc::dm::IModelStructCreateHook *getCreateHook() const override;

	virtual void setCreateHook(
        vsc::dm::IModelStructCreateHook *hook,
        bool                            owned=true) override;

	virtual vsc::dm::IModelField *mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) override;

	virtual vsc::dm::IModelField *mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type) override;

public:
	std::string								m_name;
	std::vector<vsc::dm::ITypeFieldUP>		 	m_fields;
	std::vector<vsc::dm::ITypeConstraintUP>		m_constraints;
	vsc::dm::IModelStructCreateHookUP			m_create_hook;


};

}
}
}

