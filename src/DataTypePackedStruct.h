/**
 * DataTypePackedStruct.h
 *
 * Copyright 2022 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author: 
 */
#pragma once
#include "zsp/arl/dm/IDataTypePackedStruct.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypePackedStruct : 
    public virtual IDataTypePackedStruct {
public:
    DataTypePackedStruct(
        const std::string           &name,
        Endian                      endian
    );

    virtual ~DataTypePackedStruct();

	virtual const std::string &name() const {
		return m_name;
	}

    virtual Endian getEndian() const override {
        return m_endian;
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

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
	std::string								        m_name;
    Endian                                          m_endian;
	std::vector<vsc::dm::ITypeFieldUP>		 	    m_fields;
	std::vector<vsc::dm::ITypeConstraintUP>		    m_constraints;
	vsc::dm::IModelStructCreateHookUP			    m_create_hook;

};

}
}
}


