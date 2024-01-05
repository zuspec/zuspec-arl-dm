/**
 * DataTypeArlStructValOpsDelegator.h
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
#include <map>
#include "zsp/arl/dm/IContext.h"
#include "vsc/dm/impl/ValOpsDelegatorBase.h"
#include "zsp/arl/dm/IDataTypeArlStruct.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypeArlStructValOpsDelegator :
    public virtual IDataTypeArlStruct,
    public vsc::dm::ValOpsDelegatorBase {
public:
    DataTypeArlStructValOpsDelegator(
        IContext            *ctxt,
        const std::string   &name);

    virtual ~DataTypeArlStructValOpsDelegator();

    virtual int32_t getByteSize() const override { return m_bytesz; }

    virtual void setAssociatedData(vsc::dm::IAssociatedData *data) override {
        m_associated_data = vsc::dm::IAssociatedDataUP(data);
    }

    virtual vsc::dm::IAssociatedData *getAssociatedData() const override {
        return m_associated_data.get();
    }

	virtual void finalize(vsc::dm::IContext *ctxt) override { }

	virtual const std::string &name() const { return m_name; }

	virtual void addField(
        vsc::dm::ITypeField     *f,
        bool                    owned=true);

	virtual const std::vector<vsc::dm::ITypeFieldUP> &getFields() const;

	virtual vsc::dm::ITypeField *getField(int32_t idx);

    virtual int32_t getNumBuiltin() const { 
        return m_num_builtin; 
    }

	virtual void addConstraint(
        vsc::dm::ITypeConstraint    *c,
        bool                        owned);

	virtual const std::vector<vsc::dm::ITypeConstraintUP> &getConstraints() const;

	virtual vsc::dm::IModelStructCreateHook *getCreateHook() const override;

	virtual void setCreateHook(
        vsc::dm::IModelStructCreateHook *hook,
        bool                            owned=true) override;

    virtual const std::vector<ITypeExecUP> &getExecs(ExecKindT kind) const override;

    virtual void addExec(ITypeExec *exec) override;

    virtual void addFunction(IDataTypeFunction *f, bool owned=true) override;

    virtual const std::vector<IDataTypeFunctionUP> &getFunctions() override;

	virtual vsc::dm::IModelField *mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) override;

	virtual vsc::dm::IModelField *mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type,
        const vsc::dm::ValRef           &val) override;

protected:
	std::string								        m_name;
    int32_t                                         m_bytesz;
    vsc::dm::IAssociatedDataUP                      m_associated_data;
    int32_t                                         m_num_builtin;
	std::vector<vsc::dm::ITypeFieldUP>		 	    m_fields;
	std::vector<vsc::dm::ITypeConstraintUP>		    m_constraints;
	vsc::dm::IModelStructCreateHookUP			    m_create_hook;
    static std::vector<ITypeExecUP>                 m_empty_exec_l;
    std::map<ExecKindT, std::vector<ITypeExecUP>>   m_exec_m;
    std::vector<IDataTypeFunctionUP>                m_functions;

};

}
}
}


