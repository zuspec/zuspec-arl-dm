/*
 * TaskIsDataTypeComponent.h
 *
 *  Created on: May 18, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {


class TaskIsDataTypeComponent : VisitorBase {
public:
	TaskIsDataTypeComponent();

	virtual ~TaskIsDataTypeComponent();

	IDataTypeComponent *check(vsc::dm::IDataType *t);

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override;

private:
	IDataTypeComponent				*m_comp;

};

}
}
}

