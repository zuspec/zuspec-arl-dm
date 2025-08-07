/*
 * VisitorBase.h
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */

#pragma once
#include "vsc/dm/impl/VisitorBase.h"

#include "zsp/arl/dm/IDataTypeAction.h"
#include "zsp/arl/dm/IDataTypeActivityBind.h"
#include "zsp/arl/dm/IDataTypeActivityParallel.h"
#include "zsp/arl/dm/IDataTypeActivityReplicate.h"
#include "zsp/arl/dm/IDataTypeActivitySchedule.h"
#include "zsp/arl/dm/IDataTypeActivitySequence.h"
#include "zsp/arl/dm/IDataTypeActivityTraverse.h"
#include "zsp/arl/dm/IDataTypeActivityTraverseType.h"
#include "zsp/arl/dm/IDataTypeAddrClaim.h"
#include "zsp/arl/dm/IDataTypeAddrClaimTransparent.h"
#include "zsp/arl/dm/IDataTypeAddrHandle.h"
#include "zsp/arl/dm/IDataTypeAddrSpaceC.h"
#include "zsp/arl/dm/IDataTypeAddrSpaceTransparentC.h"
#include "zsp/arl/dm/IDataTypeComponent.h"
#include "zsp/arl/dm/IDataTypeFlowObj.h"
#include "zsp/arl/dm/IDataTypeFunction.h"
#include "zsp/arl/dm/IDataTypeFunctionParamDecl.h"
#include "zsp/arl/dm/IDataTypePackedStruct.h"
#include "zsp/arl/dm/IDataTypeRegGroup.h"
#include "zsp/arl/dm/IDataTypeResource.h"
#include "zsp/arl/dm/IDataTypeArlStruct.h"
#include "zsp/arl/dm/IDataTypeTransparentAddrSpace.h"
#include "zsp/arl/dm/IDataTypeCoreLibComponent.h"
#include "zsp/arl/dm/IDataTypePureComponent.h"
#include "zsp/arl/dm/IDataTypeReg.h"
#include "zsp/arl/dm/IModelActivityBind.h"
#include "zsp/arl/dm/IModelActivityParallel.h"
#include "zsp/arl/dm/IModelActivityReplicate.h"
#include "zsp/arl/dm/IModelActivitySchedule.h"
#include "zsp/arl/dm/IModelActivityScope.h"
#include "zsp/arl/dm/IModelActivitySequence.h"
#include "zsp/arl/dm/IModelActivityTraverse.h"
#include "zsp/arl/dm/IModelFieldAction.h"
#include "zsp/arl/dm/IModelFieldClaim.h"
#include "zsp/arl/dm/IModelFieldComponent.h"
#include "zsp/arl/dm/IModelFieldComponentRoot.h"
#include "zsp/arl/dm/IModelFieldExecutor.h"
#include "zsp/arl/dm/IModelFieldExecutorClaim.h"
#include "zsp/arl/dm/IModelFieldInOut.h"
#include "zsp/arl/dm/IModelFieldPool.h"
#include "zsp/arl/dm/IModelFieldRegGroup.h"
#include "zsp/arl/dm/IVisitor.h"
#include "zsp/arl/dm/ITypeExprMethodCallContext.h"
#include "zsp/arl/dm/ITypeExprMethodCallStatic.h"
#include "zsp/arl/dm/ITypeExprPyImportRef.h"
#include "zsp/arl/dm/ITypeExprPythonFieldRef.h"
#include "zsp/arl/dm/ITypeExprPythonMethodCall.h"
#include "zsp/arl/dm/ITypeExprPythonModuleRef.h"
#include "zsp/arl/dm/ITypeExecProc.h"
#include "zsp/arl/dm/ITypeFieldActivity.h"
#include "zsp/arl/dm/ITypeFieldAddrClaim.h"
#include "zsp/arl/dm/ITypeFieldAddrClaimTransparent.h"
#include "zsp/arl/dm/ITypeFieldClaim.h"
#include "zsp/arl/dm/ITypeFieldExecutor.h"
#include "zsp/arl/dm/ITypeFieldExecutorClaim.h"
#include "zsp/arl/dm/ITypeFieldInOut.h"
#include "zsp/arl/dm/ITypeFieldPool.h"
#include "zsp/arl/dm/ITypeFieldReg.h"
#include "zsp/arl/dm/ITypeFieldRegGroup.h"
#include "zsp/arl/dm/ITypeFieldRegGroupArr.h"
#include "zsp/arl/dm/ITypeProcStmtAssign.h"
#include "zsp/arl/dm/ITypeProcStmtBreak.h"
#include "zsp/arl/dm/ITypeProcStmtContinue.h"
#include "zsp/arl/dm/ITypeProcStmtExpr.h"
#include "zsp/arl/dm/ITypeProcStmtForeach.h"
#include "zsp/arl/dm/ITypeProcStmtIfClause.h"
#include "zsp/arl/dm/ITypeProcStmtIfElse.h"
#include "zsp/arl/dm/ITypeProcStmtMatch.h"
#include "zsp/arl/dm/ITypeProcStmtRepeat.h"
#include "zsp/arl/dm/ITypeProcStmtRepeatWhile.h"
#include "zsp/arl/dm/ITypeProcStmtReturn.h"
#include "zsp/arl/dm/ITypeProcStmtScope.h"
#include "zsp/arl/dm/ITypeProcStmtVarDecl.h"
#include "zsp/arl/dm/ITypeProcStmtWhile.h"
#include "zsp/arl/dm/ITypeProcStmtYield.h"

namespace zsp {
namespace arl {
namespace dm {


class VisitorBase : public virtual arl::dm::IVisitor, public vsc::dm::VisitorBase {
public:

	VisitorBase(bool cascade=true, vsc::dm::IVisitor *this_p=0) : vsc::dm::VisitorBase(cascade, this_p) { }

	VisitorBase(arl::dm::IVisitor *this_p) : vsc::dm::VisitorBase(this_p) { }

	virtual ~VisitorBase() { }

	virtual void visitDataTypeAction(IDataTypeAction *i) override {
		m_this->visitDataTypeStruct(i);
		for (std::vector<ITypeFieldActivityUP>::const_iterator
				it=i->activities().begin();
				it!=i->activities().end(); it++) {
			(*it)->accept(m_this);
		}
	}

    virtual void visitDataTypeActivity(IDataTypeActivity *t) override { }

	virtual void visitDataTypeActivityBind(IDataTypeActivityBind *t) override {
        visitDataTypeActivity(t);
		for (std::vector<vsc::dm::ITypeExprFieldRefUP>::const_iterator
			it=t->getTargets().begin();
			it!=t->getTargets().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitDataTypeActivityParallel(IDataTypeActivityParallel *t) override {
        visitDataTypeActivity(t);
		m_this->visitDataTypeStruct(t);
	}

	virtual void visitDataTypeActivityReplicate(IDataTypeActivityReplicate *t) override {
        visitDataTypeActivity(t);
		t->getCount()->accept(m_this);
		m_this->visitDataTypeStruct(t);
	}

	virtual void visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) override {
        visitDataTypeActivity(t);
		m_this->visitDataTypeStruct(t);
	}

	virtual void visitDataTypeActivitySequence(IDataTypeActivitySequence *t) override {
        visitDataTypeActivity(t);
		m_this->visitDataTypeStruct(t);
		for (std::vector<ITypeFieldActivityUP>::const_iterator
				it=t->getActivities().begin();
				it!=t->getActivities().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) override { 
        visitDataTypeActivity(t);
    }

	virtual void visitDataTypeActivityTraverseType(IDataTypeActivityTraverseType *t) override { 
        visitDataTypeActivity(t);
        t->getTarget()->accept(m_this);
    }

	virtual void visitDataTypeAddrClaim(IDataTypeAddrClaim *t) override {
        visitDataTypeArlStruct(t);
    }

	virtual void visitDataTypeAddrClaimTransparent(IDataTypeAddrClaimTransparent *t) override {
        visitDataTypeAddrClaim(t);
    }

	virtual void visitDataTypeAddrSpaceC(IDataTypeAddrSpaceC *t) override {
        m_this->visitDataTypeStruct(t);
    }

	virtual void visitDataTypeAddrSpaceTransparentC(IDataTypeAddrSpaceTransparentC *t) override {
        visitDataTypeAddrSpaceC(t);
    }

	virtual void visitDataTypeAddrHandle(IDataTypeAddrHandle *t) override {
        m_this->visitDataTypeStruct(t);
    }

	virtual void visitDataTypeArlStruct(IDataTypeArlStruct *t) override {
		m_this->visitDataTypeStruct(t);
	}

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override {
		m_this->visitDataTypeStruct(t);
        for (std::vector<ITypeFieldActivityUP>::const_iterator
            it=t->activities().begin();
            it!=t->activities().end(); it++) {
            (*it)->accept(m_this);
        }
	}

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override {
		m_this->visitDataTypeStruct(t);
	}

	virtual void visitDataTypeFunction(IDataTypeFunction *t) override {

	}
    
	virtual void visitDataTypeFunctionParamDecl(IDataTypeFunctionParamDecl *t) override {
        t->getDataType()->accept(m_this);
        if (t->getInit()) {
            t->getInit()->accept(m_this);
        }
    }

	virtual void visitDataTypePackedStruct(IDataTypePackedStruct *t) override {
        m_this->visitDataTypeStruct(t);
    }

    virtual void visitDataTypePyObj(IDataTypePyObj *t) override {
        // 
    }

    virtual void visitDataTypeRegGroup(IDataTypeRegGroup *t) override {
        dynamic_cast<IVisitor *>(m_this)->visitDataTypeComponent(t);
    }

virtual void visitDataTypeResource(IDataTypeResource *t) override {
    dynamic_cast<IVisitor *>(m_this)->visitDataTypeFlowObj(t);
}

virtual void visitDataTypeTransparentAddrSpace(IDataTypeTransparentAddrSpace *t) override {
    m_this->visitDataTypeStruct(t);
}

virtual void visitDataTypeCoreLibComponent(IDataTypeCoreLibComponent *t) override {
    dynamic_cast<IVisitor *>(m_this)->visitDataTypeComponent(t);
}

virtual void visitDataTypePureComponent(IDataTypePureComponent *t) override {
    dynamic_cast<IVisitor *>(m_this)->visitDataTypeArlStruct(t);
}

virtual void visitDataTypeReg(IDataTypeReg *t) override {
    m_this->visitDataTypeStruct(t);
}

	virtual void visitModelActivityBind(IModelActivityBind *a) override {
		for (std::vector<vsc::dm::IModelExprUP>::const_iterator
			it=a->getTargets().begin();
			it!=a->getTargets().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override {
		for (std::vector<IModelActivity *>::const_iterator
				it=a->branches().begin();
				it!=a->branches().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitModelActivityReplicate(IModelActivityReplicate *a) override {
		a->getCountExpr()->accept(m_this);
		visitModelActivityScope(a);
	}

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override {
		for (std::vector<IModelActivity *>::const_iterator
				it=a->activities().begin();
				it!=a->activities().end(); it++) {
			(*it)->accept(m_this);
		}
	}
	
	virtual void visitModelActivityScope(IModelActivityScope *a) override {
		for (std::vector<IModelActivity *>::const_iterator
				it=a->activities().begin();
				it!=a->activities().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override {
		for (std::vector<IModelActivity *>::const_iterator
				it=a->activities().begin();
				it!=a->activities().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override {
		a->getTarget()->accept(m_this);
		if (a->getWithC()) {
			a->getWithC()->accept(m_this);
		}
	}

	virtual void visitModelFieldAction(IModelFieldAction *f) override {
		m_this->visitModelField(f);
		if (f->getActivity()) {
			f->getActivity()->accept(m_this);
		}
	}

	virtual void visitModelFieldClaim(IModelFieldClaim *f) override { }

	virtual void visitModelFieldComponent(IModelFieldComponent *f) override {
		m_this->visitModelField(f);
	}

	virtual void visitModelFieldComponentRoot(IModelFieldComponentRoot *f) override {
		visitModelFieldComponent(f);
	}

	virtual void visitModelFieldExecutor(IModelFieldExecutor *f) override {
		m_this->visitModelField(f);
	}

	virtual void visitModelFieldExecutorClaim(IModelFieldExecutorClaim *f) override {
		m_this->visitModelFieldRef(f);
	}

	virtual void visitModelFieldInOut(IModelFieldInOut *f) override { }

	virtual void visitModelFieldPool(IModelFieldPool *f) override {
		m_this->visitModelField(f);
	}

	virtual void visitModelFieldRegGroup(IModelFieldRegGroup *f) override {
        m_this->visitModelField(f);
    }

    virtual void visitTypeExprMethodCallContext(ITypeExprMethodCallContext *e) override {
        visitTypeExprMethodCallStatic(e);
        e->getContext()->accept(m_this);
    }

    virtual void visitTypeExprMethodCallStatic(ITypeExprMethodCallStatic *e) override {
        if (e->getTarget()) {
            e->getTarget()->accept(m_this);
        }
    }

	virtual void visitTypeExec(ITypeExec *e) override { }

	virtual void visitTypeExecProc(ITypeExecProc *e) override {
        dynamic_cast<IVisitor *>(m_this)->visitTypeExec(e);
        e->getBody()->accept(m_this);
    }

    virtual void visitTypeExprPyImportRef(ITypeExprPyImportRef *t) override { }

    virtual void visitTypeExprPythonFieldRef(ITypeExprPythonFieldRef *t) override {
        t->getBase()->accept(m_this);
    }

    virtual void visitTypeExprPythonMethodCall(ITypeExprPythonMethodCall *t) override {
    }

    virtual void visitTypeExprPythonModuleRef(ITypeExprPythonModuleRef *t) override {
        //
    }

	virtual void visitTypeFieldActivity(ITypeFieldActivity *f) override {
		m_this->visitTypeField(f);
	}

	virtual void visitTypeFieldAddrClaim(ITypeFieldAddrClaim *f) override {
        m_this->visitTypeField(f);
    }

	virtual void visitTypeFieldAddrClaimTransparent(ITypeFieldAddrClaimTransparent *f) override {
        dynamic_cast<IVisitor *>(m_this)->visitTypeFieldAddrClaim(f);
    }

	virtual void visitTypeFieldClaim(ITypeFieldClaim *f) override {
		m_this->visitTypeFieldRef(f);
	}

	virtual void visitTypeFieldExecutor(ITypeFieldExecutor *f) override {
		m_this->visitTypeField(f);
	}

	virtual void visitTypeFieldExecutorClaim(ITypeFieldExecutorClaim *f) override {
		m_this->visitTypeFieldRef(f);
	}

	virtual void visitTypeFieldInOut(ITypeFieldInOut *f) override {
		m_this->visitTypeFieldRef(f);
	}

	virtual void visitTypeFieldPool(ITypeFieldPool *f) override {
		m_this->visitTypeField(f);
	}

	virtual void visitTypeFieldReg(ITypeFieldReg *f) override {
        m_this->visitTypeField(f);
    }

	virtual void visitTypeFieldRegGroup(ITypeFieldRegGroup *f) override {
        m_this->visitTypeField(f);
    }

	virtual void visitTypeFieldRegGroupArr(ITypeFieldRegGroupArr *f) override {
        dynamic_cast<IVisitor *>(m_this)->visitTypeFieldRegGroup(f);
    }

	virtual void visitTypeProcStmt(ITypeProcStmt *s) override { }

	virtual void visitTypeProcStmtAssign(ITypeProcStmtAssign *s) override {
        visitTypeProcStmt(s);
		s->getLhs()->accept(m_this);
		s->getRhs()->accept(m_this);
	}

	virtual void visitTypeProcStmtBreak(ITypeProcStmtBreak *s) override {
        visitTypeProcStmt(s);
	}

	virtual void visitTypeProcStmtContinue(ITypeProcStmtContinue *s) override {
        visitTypeProcStmt(s);
	}

	virtual void visitTypeProcStmtExpr(ITypeProcStmtExpr *s) override {
        visitTypeProcStmt(s);
        s->getExpr()->accept(m_this);
	}

	virtual void visitTypeProcStmtForeach(ITypeProcStmtForeach *s) override {
        visitTypeProcStmt(s);
	}
    
	virtual void visitTypeProcStmtIfClause(ITypeProcStmtIfClause *s) override {
        visitTypeProcStmt(s);
        s->getCond()->accept(m_this);
        if (s->getStmt()) {
            s->getStmt()->accept(m_this);
        }
    }

	virtual void visitTypeProcStmtIfElse(ITypeProcStmtIfElse *s) override {
        for (std::vector<ITypeProcStmtIfClauseUP>::const_iterator
            it=s->getIfClauses().begin();
            it!=s->getIfClauses().end(); it++) {
            (*it)->accept(m_this);
        }
        if (s->getElseClause()) {
            s->getElseClause()->accept(m_this);
        }
	}

	virtual void visitTypeProcStmtMatch(ITypeProcStmtMatch *s) override {
        visitTypeProcStmt(s);
		s->getCond()->accept(m_this);
	}

	virtual void visitTypeProcStmtRepeat(ITypeProcStmtRepeat *s) override {
        visitTypeProcStmt(s);
		s->getExpr()->accept(m_this);
		s->getBody()->accept(m_this);
	}

	virtual void visitTypeProcStmtRepeatWhile(ITypeProcStmtRepeatWhile *s) override {
        visitTypeProcStmt(s);
		s->getExpr()->accept(m_this);
		s->getBody()->accept(m_this);
	}

	virtual void visitTypeProcStmtReturn(ITypeProcStmtReturn *s) override {
        visitTypeProcStmt(s);
		if (s->getExpr()) {
			s->getExpr()->accept(m_this);
		}
	}

	virtual void visitTypeProcStmtScope(ITypeProcStmtScope *s) override {
        visitTypeProcStmt(s);
		for (std::vector<ITypeProcStmtUP>::const_iterator
			it=s->getStatements().begin();
			it!=s->getStatements().end(); it++) {
			(*it)->accept(m_this);
		}
	}

	virtual void visitTypeProcStmtVarDecl(ITypeProcStmtVarDecl *s) override {
        visitTypeProcStmt(s);
		s->getDataType()->accept(m_this);
		if (s->getInit()) {
			s->getInit()->accept(m_this);
		}
	}

	virtual void visitTypeProcStmtWhile(ITypeProcStmtWhile *s) override {
        visitTypeProcStmt(s);
		s->getCond()->accept(m_this);
		s->getBody()->accept(m_this);
	}

	virtual void visitTypeProcStmtYield(ITypeProcStmtYield *s) override { 
        visitTypeProcStmt(s);
    }
};

}
}
}
