/*
 * ModelActivityParallel.h
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelActivityParallel.h"
#include "ModelActivityScope.h"
#include "ModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class ModelActivityParallel : 
	public virtual IModelActivityParallel,
	public virtual ModelActivityScope {
public:
	ModelActivityParallel();

	virtual ~ModelActivityParallel();

	virtual const std::string &name() const override { return m_name; }

	virtual vsc::IDataType *getDataType() const override { return 0; }

	virtual const std::vector<IModelActivity *> &branches() const override {
		return m_branches;
	}

	virtual void addBranch(IModelActivity *a) override {
		m_branches.push_back(a);
	}

	virtual void accept(vsc::IVisitor *v) override;

private:
	std::string									m_name;
	std::vector<IModelActivity *>				m_branches;

};

}
}
}

