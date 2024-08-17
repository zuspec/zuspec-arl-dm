/*
 * DataTypeArlStruct.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include <map>
#include <string>
#include <vector>
#include "vsc/dm/impl/ValRef.h"
#include "zsp/arl/dm/IDataTypeArlStruct.h"
#include "DataTypeArl.h"

namespace vsc {
namespace dm {
    class IModelBuildContext;
    class IModelStructCreateHook;
    class ITypeField;
    class ITypeConstraint;
}
}

namespace zsp {
namespace arl {
namespace dm {


class DataTypeArlStruct : 
    public virtual IDataTypeArlStruct,
    public virtual DataTypeArl {
public:
	DataTypeArlStruct(
        const std::string   &name,
        int32_t             num_builtin=0);

	virtual ~DataTypeArlStruct();

    virtual void initVal(vsc::dm::ValRef &v) override { }

    virtual void finiVal(vsc::dm::ValRef &v) override { }

    virtual vsc::dm::ValRef copyVal(const vsc::dm::ValRef &src) override { 
        return vsc::dm::ValRef();
    }

	virtual void finalize(vsc::dm::IContext *ctxt) override { }

	virtual const std::string &name() const {
		return m_name;
	}

	virtual void addField(
        vsc::dm::ITypeField     *f,
        bool                    owned=true);

	virtual const std::vector<vsc::dm::ITypeFieldUP> &getFields() const;

	virtual vsc::dm::ITypeField *getField(int32_t idx);

    virtual int32_t getNumBuiltin() const { 
        return m_num_builtin; 
    }

    virtual vsc::dm::IDataTypeStruct *getSuper() override {
        return m_super.get();
    }

    virtual void setSuper(vsc::dm::IDataTypeStruct *t, bool owned=false) override {
        m_super  = vsc::dm::IDataTypeStructUP(t, owned);
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

    virtual void accept(vsc::dm::IVisitor *v) override;

public:
	std::string								        m_name;
    int32_t                                         m_num_builtin;
	std::vector<vsc::dm::ITypeFieldUP>		 	    m_fields;
    vsc::dm::IDataTypeStructUP                      m_super;
	std::vector<vsc::dm::ITypeConstraintUP>		    m_constraints;
	vsc::dm::IModelStructCreateHookUP			    m_create_hook;
    static std::vector<ITypeExecUP>                 m_empty_exec_l;
    std::map<ExecKindT, std::vector<ITypeExecUP>>   m_exec_m;
    std::vector<IDataTypeFunctionUP>                m_functions;

};

}
}
}

