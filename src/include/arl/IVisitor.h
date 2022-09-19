/*
 * IVisitor.h
 *
 *  Created on: Apr 2, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/IVisitor.h"

namespace arl {

class IDataTypeAction;
class IDataTypeActivityParallel;
class IDataTypeActivitySchedule;
class IDataTypeActivitySequence;
class IDataTypeActivityTraverse;
class IDataTypeComponent;
class IDataTypeFlowObj;
class IDataTypeResource;
class IModelActivityParallel;
class IModelActivitySchedule;
class IModelActivitySequence;
class IModelActivityTraverse;
class IModelFieldAction;
class IModelFieldComponent;
class IModelFieldPool;
class ITypeFieldActivity;
class ITypeFieldClaim;
class ITypeFieldInOut;
class ITypeFieldPool;

class IVisitor : public virtual vsc::IVisitor {
public:

	virtual ~IVisitor() { }

	virtual void visitDataTypeAction(IDataTypeAction *t) = 0;

	virtual void visitDataTypeActivityParallel(IDataTypeActivityParallel *t) = 0;

	virtual void visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) = 0;

	virtual void visitDataTypeActivitySequence(IDataTypeActivitySequence *t) = 0;

	virtual void visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) = 0;

	virtual void visitDataTypeComponent(IDataTypeComponent *t) = 0;

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) = 0;

	virtual void visitDataTypeResource(IDataTypeResource *t) = 0;

	virtual void visitModelActivityParallel(IModelActivityParallel *a) = 0;

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) = 0;

	virtual void visitModelActivitySequence(IModelActivitySequence *a) = 0;

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) = 0;

	virtual void visitModelFieldAction(IModelFieldAction *f) = 0;

	virtual void visitModelFieldComponent(IModelFieldComponent *f) = 0;

	virtual void visitModelFieldPool(IModelFieldPool *f) = 0;

	virtual void visitTypeFieldActivity(ITypeFieldActivity *f) = 0;

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) = 0;

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) = 0;

	virtual void visitTypeFieldPool(ITypeFieldPool *f) = 0;

};

}
