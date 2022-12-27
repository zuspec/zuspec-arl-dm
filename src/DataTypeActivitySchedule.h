/*
 * DataTypeActivitySchedule.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include "DataTypeActivityScope.h"
#include "zsp/arl/dm/IDataTypeActivitySchedule.h"

namespace zsp {
namespace arl {
namespace dm {


class DataTypeActivitySchedule :
		public virtual IDataTypeActivitySchedule,
		public virtual DataTypeActivityScope {
public:
	DataTypeActivitySchedule();

	virtual ~DataTypeActivitySchedule();

	virtual IModelActivity *mkActivity(
		vsc::dm::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) override;

	virtual void accept(vsc::dm::IVisitor *v) override;

private:

};

}
}
}

