/*
 * ModelEvalIteratorSeq.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#include <stdio.h>
#include "ModelEvalIterator.h"

namespace arl {

ModelEvalIterator::ModelEvalIterator(const ModelEvalIterator::Elem &elem) {
	m_idx = -1;
	m_seq.push_back(elem);
}

ModelEvalIterator::ModelEvalIterator(const std::vector<ModelEvalIterator::Elem> &seq) :
		m_seq(seq.begin(), seq.end()), m_idx(-1) {
	fprintf(stdout, "Size: %d\n", m_seq.size());
	// TODO Auto-generated constructor stub

}

ModelEvalIterator::~ModelEvalIterator() {
	// TODO Auto-generated destructor stub
}

bool ModelEvalIterator::next() {
	fprintf(stdout, "next: idx=%d size=%d\n", m_idx, m_seq.size());
	m_idx++;
	if (m_idx < m_seq.size()) {
		fprintf(stdout, "Return true\n");
		return true;
	} else {
		fprintf(stdout, "Return false\n");
		delete this;
		return false;
	}
}

bool ModelEvalIterator::valid() {
	return (m_idx >= 0 && m_idx < m_seq.size());
}

ModelEvalNodeT ModelEvalIterator::type() const {
	return m_seq.at(m_idx).type;
}

IModelFieldAction *ModelEvalIterator::action() {
	fprintf(stdout, "ModelEvalIterator::action %d %p\n", 
		m_idx, m_seq.at(m_idx).action);
	return m_seq.at(m_idx).action;
}

IModelEvalIterator *ModelEvalIterator::iterator() {
	return m_seq.at(m_idx).iterator;
}


} /* namespace arl */
