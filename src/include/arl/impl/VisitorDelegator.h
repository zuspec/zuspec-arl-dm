/*
 * VisitorDelegator.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IDataTypeResource.h"
#include "arl/IVisitor.h"
#include "arl/ITypeFieldPool.h"
#include "arl/IModelFieldAction.h"
#include "arl/IModelActivityParallel.h"
#include "arl/IModelActivitySchedule.h"
#include "arl/IModelActivitySequence.h"
#include "arl/IModelActivityTraverse.h"
#include "vsc/impl/VisitorDelegator.h"

namespace arl {

class VisitorDelegator : public virtual arl::IVisitor, public vsc::VisitorDelegator {
public:
	VisitorDelegator(vsc::IVisitor *delegate) : vsc::VisitorDelegator(delegate) { }

	VisitorDelegator(arl::IVisitor *delegate) : vsc::VisitorDelegator(delegate) { }

	virtual void visitDataTypeAction(IDataTypeAction *i) override {
		delegate(&arl::IVisitor::visitDataTypeAction,
				&vsc::IVisitor::visitDataTypeStruct, i);
	}

	virtual void visitDataTypeActivityParallel(IDataTypeActivityParallel *t) override {
		delegate(&arl::IVisitor::visitDataTypeActivityParallel,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) override {
		delegate(&arl::IVisitor::visitDataTypeActivitySchedule,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivitySequence(IDataTypeActivitySequence *t) override {
		delegate(&arl::IVisitor::visitDataTypeActivitySequence,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) override {
		delegate(&arl::IVisitor::visitDataTypeActivityTraverse, t);
	}

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override {
		delegate(&arl::IVisitor::visitDataTypeComponent,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override {
		delegate(&arl::IVisitor::visitDataTypeFlowObj,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeResource(IDataTypeResource *t) override {
		delegate(&arl::IVisitor::visitDataTypeResource,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override {
		delegate(&arl::IVisitor::visitModelActivityParallel, a);
	}

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override {
		delegate(&arl::IVisitor::visitModelActivitySchedule, a);
	}

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override {
		delegate(&arl::IVisitor::visitModelActivitySequence, a);
	}

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override {
		delegate(&arl::IVisitor::visitModelActivityTraverse, a);
	}

	virtual void visitModelFieldAction(IModelFieldAction *f) override {
		delegate(&arl::IVisitor::visitModelFieldAction,
				&vsc::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldComponent(IModelFieldComponent *f) override {
		delegate(&arl::IVisitor::visitModelFieldComponent,
				&vsc::IVisitor::visitModelField, f);
	}

	virtual void visitModelFieldPool(IModelFieldPool *f) override {
		delegate(&arl::IVisitor::visitModelFieldPool,
				&vsc::IVisitor::visitModelField, f);
	}

	virtual void visitTypeFieldActivity(ITypeFieldActivity *f) override {
		delegate(&arl::IVisitor::visitTypeFieldActivity,
				&vsc::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) override {
		delegate(&arl::IVisitor::visitTypeFieldClaim,
				&vsc::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) override {
		delegate(&arl::IVisitor::visitTypeFieldInOut,
				&vsc::IVisitor::visitTypeField, f);
	}

	virtual void visitTypeFieldPool(ITypeFieldPool *f) override {
		delegate(&arl::IVisitor::visitTypeFieldPool,
				&vsc::IVisitor::visitTypeField, f);
	}

private:

	template <class T1, class T2> void delegate(
			void (arl::IVisitor::*f1)(T1 *),
			void (vsc::IVisitor::*f2)(T2 *),
			T1 *v) {
		if (delegate()) {
			((*delegate()).*f1)(v);
		} else if (m_delegate->cascade()) {
			((*vsc::VisitorDelegator::delegate()).*f2)(v);
		}
	}

	template <class T1> void delegate(
			void (arl::IVisitor::*f1)(T1 *),
			T1 *v) {
		if (delegate()) {
			((*delegate()).*f1)(v);
		} else {
			// TODO: fatal
		}
	}

	arl::IVisitor *delegate() const { return dynamic_cast<arl::IVisitor *>(m_delegate); }
};

}
