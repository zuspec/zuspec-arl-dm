/*
 * ModelEvalIteratorSeq.h
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#pragma once
#include <vector>
#include "arl/IModelEvalIterator.h"

namespace arl {


class ModelEvalIterator : public IModelEvalIterator {
public:
	struct Elem {
		ModelEvalNodeT		type;
		union {
			vsc::IModelField	*action;
			IModelEvalIterator	*iterator;
		};
	};
public:
	ModelEvalIterator(const std::vector<Elem> &seq);

	virtual ~ModelEvalIterator();

	virtual bool next() override;

	virtual ModelEvalNodeT type() const override;

	virtual vsc::IModelField *action() override;

	virtual IModelEvalIterator *iterator() override;

private:
	std::vector<Elem>						m_seq;
	int32_t									m_idx;


};

} /* namespace arl */

