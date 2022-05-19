/*
 * TaskIsDataTypeComponent.cpp
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#include "TaskIsDataTypeComponent.h"

namespace arl {

TaskIsDataTypeComponent::TaskIsDataTypeComponent() : m_comp(0) {
	// TODO Auto-generated constructor stub

}

TaskIsDataTypeComponent::~TaskIsDataTypeComponent() {
	// TODO Auto-generated destructor stub
}

IDataTypeComponent *TaskIsDataTypeComponent::check(vsc::IDataType *t) {
	m_comp = 0;
	t->accept(this);
	return m_comp;
}

void TaskIsDataTypeComponent::visitDataTypeComponent(IDataTypeComponent *t) {
	m_comp = t;
}

} /* namespace arl */
