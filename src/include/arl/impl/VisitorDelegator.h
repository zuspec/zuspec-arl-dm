/*
 * VisitorDelegator.h
 *
 *  Created on: Apr 28, 2022
 *      Author: mballance
 */

#pragma once
#include "arl/IVisitor.h"
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

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override {
		delegate(&arl::IVisitor::visitDataTypeComponent,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override {
		delegate(&arl::IVisitor::visitDataTypeFlowObj,
				&vsc::IVisitor::visitDataTypeStruct, t);
	}

	virtual void visitTypeActivityStmtTraverseType(ITypeActivityStmtTraverseType *s) override {
		delegate(&arl::IVisitor::visitTypeActivityStmtTraverseType, s);
	}

private:

	template <class T1, class T2> void delegate(
			void (arl::IVisitor::*f1)(T1 *),
			void (vsc::IVisitor::*f2)(T2 *),
			T1 *v) {
		if (delegate()) {
			((*delegate()).*f1)(v);
		} else {
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
