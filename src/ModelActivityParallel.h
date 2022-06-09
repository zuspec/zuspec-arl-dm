/*
 * ModelActivityParallel.h
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelActivityParallel.h"

namespace arl {

class ModelActivityParallel : public IModelActivityParallel {
public:
	ModelActivityParallel();

	virtual ~ModelActivityParallel();

	virtual const std::vector<IModelActivityUP> &getBranches() const override {
		return m_branches;
	}

	virtual void addBranch(IModelActivity *a) override {
		m_branches.push_back(IModelActivityUP(a));
	}

	virtual void accept(vsc::IVisitor *v) override;

private:
	std::vector<IModelActivityUP>				m_branches;

};

} /* namespace arl */

