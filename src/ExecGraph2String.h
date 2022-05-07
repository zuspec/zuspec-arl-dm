/*
 * ExecGraph2String.h
 *
 *  Created on: May 6, 2022
 *      Author: mballance
 */

#pragma once
#include <string>

namespace arl {

class ExecGraphNode;

class ExecGraph2String {
public:
	ExecGraph2String();

	virtual ~ExecGraph2String();

	std::string toString(ExecGraphNode *root);

private:

	void processNode(ExecGraphNode *node);

	void print(const char *fmt, ...);

	void println(const char *fmt, ...);

	void inc_indent();

	void dec_indent();

	void indent();

	const char *get_indent();

private:
	std::string			m_ind;
	std::string			m_str;
};

} /* namespace arl */

