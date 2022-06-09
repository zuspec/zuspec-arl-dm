/*
 * ModelEvalIteratorMgr.h
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelEvalIterator.h"
#include "ModelEvaluator.h"

namespace arl {

class ModelEvalIteratorMgr : public IModelEvalIterator {
public:
	ModelEvalIteratorMgr(ModelEvaluator		*eval);

	virtual ~ModelEvalIteratorMgr();

	virtual bool next() override;

	virtual ModelEvalNodeT type() const override;

	virtual IModelFieldAction *action() override;

	virtual IModelEvalIterator *iterator() override;

private:
	ModelEvaluator							*m_eval;
	std::vector<IModelEvalIterator *>		m_eval_s;

};

} /* namespace arl */

