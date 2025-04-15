/*
 * DataTypeActivityScope.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeActivityScope.h"
#include "DataTypeActivityStmt.h"

namespace zsp {
namespace arl {
namespace dm {


class DataTypeActivityScope : 
    public virtual IDataTypeActivityScope,
    public virtual DataTypeActivityStmt {
public:
	DataTypeActivityScope(const std::string &name);

	virtual ~DataTypeActivityScope();

	virtual const std::string &name() const override { return m_name; }

    virtual int32_t getByteSize() const override;

    virtual int32_t getActivityOffset() const override;

	virtual void addField(
        vsc::dm::ITypeField     *f,
        bool                    owned=true) override;

	virtual const std::vector<vsc::dm::ITypeFieldUP> &getFields() const override {
		return m_fields;
	}

	virtual vsc::dm::ITypeField *getField(int32_t idx) override {
		return m_fields.at(idx).get();
	}

    virtual int32_t getNumBuiltin() const { return 0; }


	virtual void addConstraint(
        vsc::dm::ITypeConstraint    *c,
        bool                        owned=true) override;

	virtual const std::vector<vsc::dm::ITypeConstraintUP> &getConstraints() const override {
		return m_constraints;
	}

	virtual vsc::dm::IModelStructCreateHook *getCreateHook() const override {
		return m_create_hook.get();
	}

	virtual void setCreateHook(
        vsc::dm::IModelStructCreateHook     *hook,
        bool                                owned) override {
		m_create_hook = vsc::dm::IModelStructCreateHookUP(hook, owned);
	}

	virtual const std::vector<ITypeFieldActivityUP> &getActivities() const override {
		return m_activities;
	}

	virtual void addActivity(
        ITypeFieldActivity      *a,
        bool                    owned) override;

	virtual void addActivityField(ITypeFieldActivity *a) override;

    virtual const std::vector<IDataTypeActivityBindUP> &getBinds() const override {
        return m_binds;
    }

    virtual void addBind(IDataTypeActivityBind *b) override {
        m_binds.push_back(IDataTypeActivityBindUP(b));
    };
    
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
		vsc::dm::ITypeField				*type,
        const vsc::dm::ValRef           &val) override;

private:
	std::string									m_name;
	std::vector<vsc::dm::ITypeFieldUP>			m_fields;
    int32_t                                     m_field_sz;
    int32_t                                     m_activity_sz;

	std::vector<vsc::dm::ITypeConstraintUP>		m_constraints;
	vsc::dm::IModelStructCreateHookUP			m_create_hook;

	std::vector<ITypeFieldActivityUP>			m_activities;
    std::vector<IDataTypeActivityBindUP>        m_binds;
    vsc::dm::IAssociatedDataUP                  m_associated_data;

};

}
}
}

