/*
 * ModelEvalIteratorIncrElabMgr.h
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IModelEvalIterator.h"
#include "ModelEvaluatorIncrElab.h"

namespace arl {

class ModelEvalIteratorIncrElabMgr : public IModelEvalIterator {
public:
	ModelEvalIteratorIncrElabMgr(ModelEvaluatorIncrElab *eval);

	virtual ~ModelEvalIteratorIncrElabMgr();

	virtual bool next() override;

	virtual bool pop() override { return false; }

	virtual ModelEvalNodeT type() const override;

	virtual IModelFieldAction *action() override;

	virtual IModelEvalIterator *iterator() override;

private:
	ModelEvaluatorIncrElab				*m_eval;
	std::vector<IModelEvalIterator *>		m_eval_s;

};

} /* namespace arl */

