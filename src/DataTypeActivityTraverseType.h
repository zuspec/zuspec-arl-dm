/**
 * DataTypeActivityTraverseType.h
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
 * Created on:
 *     Author: 
 */
#pragma once
#include "zsp/arl/dm/IDataTypeActivityTraverseType.h"
#include "DataTypeActivityStmt.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypeActivityTraverseType :
    public virtual IDataTypeActivityTraverseType,
    public virtual DataTypeActivityStmt {
public:
    DataTypeActivityTraverseType(
        arl::dm::IDataTypeAction        *target,
        vsc::dm::ITypeConstraint        *with_c);

    virtual ~DataTypeActivityTraverseType();
    
    virtual int32_t getByteSize() const override { return -1; }

    virtual IDataTypeAction *getTarget() const override {
        return m_target;
    }

	virtual vsc::dm::ITypeConstraint *getWithC() const override {
        return m_with_c.get();
    }

	virtual void setWithC(vsc::dm::ITypeConstraint *c) override {
        m_with_c = vsc::dm::ITypeConstraintUP(c);
    }

	virtual IModelActivity *mkActivity(
		vsc::dm::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) override { return 0; }

    virtual void setAssociatedData(vsc::dm::IAssociatedData *data, bool owned=true) override {
        m_associated_data = vsc::dm::IAssociatedDataUP(data, owned);
    }

    virtual vsc::dm::IAssociatedData *getAssociatedData() const override {
        return m_associated_data.get();
    }

	virtual vsc::dm::IModelField *mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) override { return 0; }

	virtual vsc::dm::IModelField *mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type,
        const vsc::dm::ValRef           &val) override { return 0; }


    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    arl::dm::IDataTypeAction                    *m_target;
    vsc::dm::ITypeConstraintUP                  m_with_c;
    vsc::dm::IAssociatedDataUP                  m_associated_data;

};

}
}
}


