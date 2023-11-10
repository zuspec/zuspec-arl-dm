/**
 * TypeField.h
 *
 * Copyright 2023 Matthew Ballance and Contributors
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
 *  Created on: May 13, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/ITypeField.h"

namespace zsp {
namespace arl {
namespace dm {


class TypeField : public virtual vsc::dm::ITypeField {
public:
	TypeField(
			const std::string			&name,
			vsc::dm::IDataType			*type,
			bool						owned,
			vsc::dm::TypeFieldAttr		attr);

	virtual ~TypeField();

	virtual vsc::dm::ITypeField *getParent() const override {
		return m_parent;
	}

	virtual void setParent(vsc::dm::ITypeField *p) override {
		m_parent = p;
	}

	virtual int32_t getIndex() const override { return m_idx; }

	virtual void setIndex(int32_t idx) override { m_idx = idx; }

    virtual int32_t getOffset() const override { return m_offset; }

    virtual void setOffset(int32_t off) override { m_offset = off; }

    virtual int32_t getByteSize() const override { return m_type->getByteSize(); }

	virtual const std::string &name() const { return m_name; }

	virtual vsc::dm::IDataType *getDataType() const override {
		return m_type.get();
	}

	virtual void setDataType(vsc::dm::IDataType *t, bool own=false) override {
		m_type = vsc::dm::IDataTypeUP(t, own);
	}

    virtual bool isDataTypeOwned() const override { 
        return m_type.owned();
    }

	virtual vsc::dm::ITypeField *getField(int32_t idx) const override;

	virtual vsc::dm::TypeFieldAttr getAttr() const override {
		return m_attr;
	}

	virtual vsc::dm::IModelField *mkModelField(
		vsc::dm::IModelBuildContext 		*ctxt,
        const vsc::dm::ValRef               &val) override;

protected:
	vsc::dm::ITypeField						*m_parent;
	int32_t								    m_idx;
	std::string							    m_name;
    int32_t                                 m_offset;
	vsc::dm::IDataTypeUP				    m_type;
	vsc::dm::TypeFieldAttr					m_attr;
};

}
}
}

