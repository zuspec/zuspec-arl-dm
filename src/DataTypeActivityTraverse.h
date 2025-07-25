/*
 * DataTypeActivityTraverse.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */
#pragma once
#include "zsp/arl/dm/IDataTypeActivityTraverse.h"
#include "vsc/dm/ITypeConstraint.h"
#include "DataTypeActivityStmt.h"


namespace zsp {
namespace arl {
namespace dm {


class DataTypeActivityTraverse : 
	public virtual IDataTypeActivityTraverse,
    public virtual DataTypeActivityStmt {
public:
	DataTypeActivityTraverse(
			vsc::dm::ITypeExpr		        *target,
			vsc::dm::ITypeConstraint		*with_c);

	virtual ~DataTypeActivityTraverse();

    virtual int32_t getByteSize() const override { return -1; }

	virtual vsc::dm::ITypeExpr *getTarget() const override {
		return m_target.get();
	}

	virtual vsc::dm::ITypeConstraint *getWithC() const override {
		return m_with_c.get();
	}

	virtual void setWithC(vsc::dm::ITypeConstraint *c) override {
		m_with_c = vsc::dm::ITypeConstraintUP(c);
	}

	virtual IModelActivity *mkActivity(
		vsc::dm::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) override;

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
	vsc::dm::ITypeExprUP				        m_target;
	vsc::dm::ITypeConstraintUP					m_with_c;
	vsc::dm::IModelFieldFactoryUP				m_factory;
    vsc::dm::IAssociatedDataUP                  m_associated_data;
};

}
}
}

