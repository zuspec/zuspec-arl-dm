/*
 * ModelEvalIteratorMgr.cpp
 *
 *  Created on: Jun 6, 2022
 *      Author: mballance
 */

#include "ModelEvalIteratorMgr.h"

namespace arl {

ModelEvalIteratorMgr::ModelEvalIteratorMgr(
		ModelEvaluator			*eval) : m_eval(eval) {

}

ModelEvalIteratorMgr::~ModelEvalIteratorMgr() {
	// TODO Auto-generated destructor stub
}

bool ModelEvalIteratorMgr::next() {
	bool ret = false;

	while (m_eval_s.size() > 0) {
		if (m_eval_s.back()->next()) {
			ret = true;
			break;
		}
		// Note: the iterator auto-frees on returning False
		m_eval_s.pop_back();
	}

	if (!ret) {
		// Time to go back to the source
		IModelEvalIterator *it = m_eval->next();

		if (it) {
			ret = it->next();
			if (ret) {
				m_eval_s.push_back(it);
			}
		}
	}

	return ret;
}

ModelEvalNodeT ModelEvalIteratorMgr::type() const {
	return m_eval_s.back()->type();
}

IModelFieldAction *ModelEvalIteratorMgr::action() {
	return dynamic_cast<IModelFieldAction *>(m_eval_s.back()->action());
}

IModelEvalIterator *ModelEvalIteratorMgr::iterator() {
	return m_eval_s.back()->iterator();
}


} /* namespace arl */
