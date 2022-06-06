/*
 * DataTypeActivitySequence.h
 *
 *  Created on: Jun 4, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeActivitySequence.h"
#include "DataTypeActivityScope.h"

namespace arl {

class DataTypeActivitySequence :
		public IDataTypeActivitySequence,
		public virtual DataTypeActivityScope {
public:
	DataTypeActivitySequence();

	virtual ~DataTypeActivitySequence();

	// List of: ref to vector
	// R
	// Ref to vector
	//

	virtual void accept(vsc::IVisitor *v) override;

private:


};

} /* namespace arl */

