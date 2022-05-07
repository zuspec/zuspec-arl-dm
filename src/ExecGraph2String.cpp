/*
 * ExecGraph2String.cpp
 *
 *  Created on: May 6, 2022
 *      Author: mballance
 */

#include "ExecGraph2String.h"
#include "ExecGraphNode.h"
#include <stdio.h>
#include <stdarg.h>

namespace arl {

ExecGraph2String::ExecGraph2String() {
	// TODO Auto-generated constructor stub

}

ExecGraph2String::~ExecGraph2String() {
	// TODO Auto-generated destructor stub
}

std::string ExecGraph2String::toString(ExecGraphNode *root) {
	m_str.clear();
	processNode(root);
	return m_str;
}

void ExecGraph2String::processNode(ExecGraphNode *node) {
	switch (node->kind()) {
	case ExecGraphNodeKindE::Parallel: {
		println("parallel {");
		inc_indent();
		for (auto it=node->children().begin(); it!=node->children().end(); it++) {
			processNode(it->get());
		}
		dec_indent();
		println("}");
	} break;
	case ExecGraphNodeKindE::Sequence: {
		println("sequence {");
		inc_indent();
		for (auto it=node->children().begin(); it!=node->children().end(); it++) {
			processNode(it->get());
		}
		dec_indent();
		println("}");
	} break;
	case ExecGraphNodeKindE::Traverse: {
		println("Traverse");
	} break;
	default: {
		println("Error: unknown");
	}
	}
}

void ExecGraph2String::print(const char *fmt, ...) {
	char tmp[256];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(tmp, sizeof(tmp), fmt, ap);
	m_str.append(tmp);
	va_end(ap);
}

void ExecGraph2String::println(const char *fmt, ...) {
	char tmp[256];
	va_list ap;

	va_start(ap, fmt);
	m_str.append(m_ind);
	vsnprintf(tmp, sizeof(tmp), fmt, ap);
	m_str.append(tmp);
	m_str.append("\n");
	va_end(ap);
}

void ExecGraph2String::inc_indent() {
	m_ind += "    ";
}

void ExecGraph2String::dec_indent() {
	if (m_ind.size() <= 4) {
		m_ind.clear();
	} else {
		m_ind = m_ind.substr(4);
	}
}

void ExecGraph2String::indent() {
	m_str.append(m_ind);;
}

const char *ExecGraph2String::get_indent() {
	return m_ind.c_str();
}

} /* namespace arl */
