/*
 * DataTypeActivitySequence.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include "zsp/arl/dm/IDataTypeActivitySequence.h"
#include "vsc/dm/IModelFieldFactory.h"
#include "DataTypeActivityScope.h"

namespace zsp {
namespace arl {
namespace dm {


class DataTypeActivitySequence :
		public virtual IDataTypeActivitySequence,
		public virtual DataTypeActivityScope {
public:
	DataTypeActivitySequence();

	virtual ~DataTypeActivitySequence();

	// List of: ref to vector
	// R
	// Ref to vector
	//

	virtual IModelActivity *mkActivity(
		vsc::dm::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) override;

	virtual void accept(vsc::dm::IVisitor *v) override;

private:


};

}
}
}

