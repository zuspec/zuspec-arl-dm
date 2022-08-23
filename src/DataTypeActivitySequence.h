/*
 * DataTypeActivitySequence.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeActivitySequence.h"
#include "vsc/IModelFieldFactory.h"
#include "DataTypeActivityScope.h"

namespace arl {

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
		vsc::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) override;

	virtual void accept(vsc::IVisitor *v) override;

private:


};

} /* namespace arl */

