/*
 * IModelActivityTraverse.h
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#pragma once
#include <memory>
#include "zsp/arl/dm/IModelActivity.h"
#include "zsp/arl/dm/IModelFieldAction.h"
#include "zsp/arl/dm/IModelFieldPool.h"
#include "vsc/dm/IModelConstraint.h"
#include "vsc/dm/IModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class IModelActivityTraverse;
using IModelActivityTraverseUP=std::unique_ptr<IModelActivityTraverse>;
class IModelActivityTraverse : public virtual IModelActivity {
public:

	virtual ~IModelActivityTraverse() { }

	virtual IModelFieldAction *getTarget() const = 0;

	virtual vsc::dm::IModelConstraint *getWithC() const = 0;

	virtual IModelActivity *getActivity() const = 0;

	/**
	 * @brief Get the Parent Pool object. This will be non-null
	 *        when this traversal is inferred. 
	 * 
	 * @return IModelFieldPool* 
	 */
	virtual IModelFieldPool *getParentPool() const = 0;

	virtual void setParentPool(IModelFieldPool *p) = 0;

	virtual bool getProcessed() const = 0;

	virtual void setProcessed(bool p) = 0;

};

}
}
}

