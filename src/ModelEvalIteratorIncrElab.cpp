/*
 * ModelEvalIteratorIncrElab.cpp
 *
 *  Created on: Apr 29, 2022
 *      Author: mballance
 */

#include <stdio.h>
#include "ModelEvalIteratorIncrElab.h"

namespace arl {

ModelEvalIteratorIncrElab::ModelEvalIteratorIncrElab(const ModelEvalIteratorIncrElab::Elem &elem) {
	m_idx = -1;
	m_seq.push_back(elem);
}

ModelEvalIteratorIncrElab::ModelEvalIteratorIncrElab(const std::vector<ModelEvalIteratorIncrElab::Elem> &seq) :
		m_seq(seq.begin(), seq.end()), m_idx(-1) {
	fprintf(stdout, "Size: %d\n", m_seq.size());
	// TODO Auto-generated constructor stub

}

ModelEvalIteratorIncrElab::~ModelEvalIteratorIncrElab() {
	// TODO Auto-generated destructor stub
}

bool ModelEvalIteratorIncrElab::next() {
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

bool ModelEvalIteratorIncrElab::valid() {
	return (m_idx >= 0 && m_idx < m_seq.size());
}

ModelEvalNodeT ModelEvalIteratorIncrElab::type() const {
	return m_seq.at(m_idx).type;
}

IModelFieldAction *ModelEvalIteratorIncrElab::action() {
	fprintf(stdout, "ModelEvalIteratorIncrElab::action %d %p\n", 
		m_idx, m_seq.at(m_idx).action);
	return m_seq.at(m_idx).action;
}

IModelEvalIterator *ModelEvalIteratorIncrElab::iterator() {
	return m_seq.at(m_idx).iterator;
}


} /* namespace arl */
