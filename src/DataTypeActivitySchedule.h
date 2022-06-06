/*
 * DataTypeActivitySchedule.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "DataTypeActivityScope.h"
#include "arl/IDataTypeActivitySchedule.h"

namespace arl {

class DataTypeActivitySchedule :
		public IDataTypeActivitySchedule,
		public virtual DataTypeActivityScope {
public:
	DataTypeActivitySchedule();

	virtual ~DataTypeActivitySchedule();

	virtual void accept(vsc::IVisitor *v) override;

private:

};

} /* namespace arl */

