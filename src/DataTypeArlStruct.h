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
#include "zsp/arl/dm/IDataTypeArlStruct.h"

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


class DataTypeArlStruct : public virtual IDataTypeArlStruct {
public:
	DataTypeArlStruct(const std::string &name);

	virtual ~DataTypeArlStruct();

    virtual void initVal(uintptr_t vp) override { }

    virtual void finiVal(uintptr_t vp) override { }

	virtual void finalize(vsc::dm::IContext *ctxt) override { }

	virtual const std::string &name() const {
		return m_name;
	}

    virtual int32_t getByteSize() const override {
        return m_bytesz;
    }

    virtual void setByteSize(int32_t sz) override {
        m_bytesz = sz;
    }

	virtual void addField(
        vsc::dm::ITypeField     *f,
        bool                    owned=true);

	virtual const std::vector<vsc::dm::ITypeFieldUP> &getFields() const;

	virtual vsc::dm::ITypeField *getField(int32_t idx);

    virtual int32_t getNumBuiltin() const { return 0; }

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

    virtual void setAssociatedData(vsc::dm::IAssociatedData *data) override {
        m_associated_data = vsc::dm::IAssociatedDataUP(data);
    }

    virtual vsc::dm::IAssociatedData *getAssociatedData() const override {
        return m_associated_data.get();
    }

	virtual vsc::dm::IModelField *mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) override;

	virtual vsc::dm::IModelField *mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type) override;

public:
	std::string								        m_name;
    int32_t                                         m_bytesz;
	std::vector<vsc::dm::ITypeFieldUP>		 	    m_fields;
	std::vector<vsc::dm::ITypeConstraintUP>		    m_constraints;
	vsc::dm::IModelStructCreateHookUP			    m_create_hook;
    static std::vector<ITypeExecUP>                 m_empty_exec_l;
    std::map<ExecKindT, std::vector<ITypeExecUP>>   m_exec_m;
    vsc::dm::IAssociatedDataUP                      m_associated_data;


};

}
}
}

