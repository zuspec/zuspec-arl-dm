/*
 * ModelEvalIteratorIncrElab.h
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IModelEvalIterator.h"
#include "arl/IModelFieldAction.h"

namespace arl {


class ModelEvalIteratorIncrElab : public IModelEvalIterator {
public:
	struct Elem {
		ModelEvalNodeT		type;
		union {
			IModelFieldAction	*action;
			IModelEvalIterator	*iterator;
		};
	};
public:
	ModelEvalIteratorIncrElab(const Elem &elem);

	ModelEvalIteratorIncrElab(const std::vector<Elem> &seq);

	virtual ~ModelEvalIteratorIncrElab();

	virtual bool next() override;

	virtual bool valid() override;

	virtual bool pop() override { return false; }

	virtual ModelEvalNodeT type() const override;

	virtual IModelFieldAction *action() override;

	virtual IModelEvalIterator *iterator() override;

private:
	std::vector<Elem>						m_seq;
	int32_t									m_idx;


};

} /* namespace arl */

