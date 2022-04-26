/*
 * DataTypeAction.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#include "DataTypeAction.h"

namespace arl {

DataTypeAction::DataTypeAction(const std::string &name) : DataTypeStruct(name),
		m_component_t(0) {

}

DataTypeAction::~DataTypeAction() {
	// TODO Auto-generated destructor stub
}

void DataTypeAction::accept(vsc::IVisitor *v) {
	/* TODO */
}

void DataTypeAction::accept(IVisitor *v) {
	/* TODO */
}

} /* namespace arl */
