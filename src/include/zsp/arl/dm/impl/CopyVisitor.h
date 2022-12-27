/**
 * CopyVisitor.h
 *
 * Copyright 2022 Matthew Ballance and Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may 
 * not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
 * See the License for the specific language governing permissions and 
 * limitations under the License.
 *
 * Created on:
 *     Author: 
 */
#pragma once
#include "arl/IContext.h"
#include "arl/IModelBuildContext.h"
#include "arl/impl/ModelBuildContext.h"
#include "arl/impl/VisitorDelegator.h"
#include "vsc/impl/CopyVisitor.h"
#include "vsc/impl/DebugMacros.h"

namespace zsp {
namespace arl {
namespace dm {



class CopyVisitor : public virtual VisitorDelegator {
public:
    CopyVisitor(
        IContext                *ctxt,
        IModelBuildContext      *build_ctxt=0) : VisitorDelegator(&m_core), 
        m_ctxt(ctxt), m_build_ctxt(build_ctxt?build_ctxt:&m_build_ctxt_l),
        m_build_ctxt_l(ctxt), m_core(ctxt, m_build_ctxt, this) { 
        DEBUG_INIT("CopyVisitor", ctxt->getDebugMgr());
    }

    virtual ~CopyVisitor() { }

    vsc::IAccept *copy(vsc::IAccept *o) {
        return m_core.copy(o);
    }

    template <class T> T *copyT(vsc::IAccept *o) {
        return dynamic_cast<T *>(copy(o));
    }

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override {

    }

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override { }

	virtual void visitDataTypeFunction(IDataTypeFunction *t) override { }

	virtual void visitDataTypeResource(IDataTypeResource *t) override { }

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override { }

	virtual void visitModelActivityReplicate(IModelActivityReplicate *a) override { 
        vsc::IModelExpr *count_e = copyT<vsc::IModelExpr>(a->getCountExpr());
        IModelActivityReplicate *ac = m_ctxt->mkModelActivityReplicate(count_e);

        for (std::vector<vsc::IModelFieldUP>::const_iterator
            it=a->fields().begin();
            it!=a->fields().end(); it++) {
            ac->addField(copyT<vsc::IModelField>(it->get()));
        }
        
        for (std::vector<vsc::IModelConstraintUP>::const_iterator
            it=a->constraints().begin();
            it!=a->constraints().end(); it++) {
            ac->addConstraint(copyT<vsc::IModelConstraint>(it->get()));
        }

        for (std::vector<IModelActivity *>::const_iterator
            it=a->activities().begin();
            it!=a->activities().end(); it++) {
            IModelActivity *it_c = copyT<IModelActivity>(*it);
            ac->addActivity(it_c, true);
        }

        ret(ac);
    }

	virtual void visitModelActivitySchedule(IModelActivitySchedule *a) override { }

	virtual void visitModelActivityScope(IModelActivityScope *a) override { 
        IModelActivityScope *ac = m_ctxt->mkModelActivityScope(a->getType());

        for (std::vector<IModelActivity *>::const_iterator
            it=a->activities().begin();
            it!=a->activities().end(); it++) {
            IModelActivity *it_c = copyT<IModelActivity>(*it);
            ac->addActivity(it_c, true);
        }

        ret(ac);
    }

	virtual void visitModelActivitySequence(IModelActivitySequence *a) override { }

	virtual void visitModelActivityTraverse(IModelActivityTraverse *a) override { 
        DEBUG_ENTER("visitModelActivityTravserse");
        vsc::IModelConstraint *with_c = 0;
        if (a->getWithC()) {
            with_c = copyT<vsc::IModelConstraint>(a->getWithC());
        }

        DEBUG("target=%p target_c=%p", 
            a->getTarget(), get_copyT<IModelFieldAction>(a->getTarget()));

        IModelActivity *activity = 0;
        if (a->getActivity()) {
            activity = copyT<IModelActivity>(a->getActivity());
        }

        IModelActivityTraverse *ac = m_ctxt->mkModelActivityTraverse(
            get_copyT<IModelFieldAction>(a->getTarget()),
            with_c,
            true,
            activity,
            true
        );

        ret(ac);
        DEBUG_LEAVE("visitModelActivityTravserse");
    }

	virtual void visitModelFieldAction(IModelFieldAction *f) override {
        DEBUG_ENTER("visitModelFieldAction");
        IModelFieldAction *fc = m_ctxt->mkModelFieldActionRoot(
            f->name(),
            f->getDataTypeT<IDataTypeAction>()
        );

        DEBUG("src=%p copy=%p", f, fc);
        add_copy(f, fc);

        for (std::vector<vsc::IModelFieldUP>::const_iterator
            it=f->fields().begin();
            it!=f->fields().end(); it++) {
            fc->addField(copyT<vsc::IModelField>(it->get()));
        }

        for (std::vector<vsc::IModelConstraintUP>::const_iterator
            it=f->constraints().begin();
            it!=f->constraints().end(); it++) {
            fc->addConstraint(copyT<vsc::IModelConstraint>(it->get()));
        }

        if (f->getActivity()) {
            fc->setActivity(copyT<IModelActivityScope>(f->getActivity()));
        }
        DEBUG_LEAVE("visitModelFieldAction");
    }

	virtual void visitModelFieldComponent(IModelFieldComponent *f) override { }

	virtual void visitModelFieldExecutor(IModelFieldExecutor *f) override { }

	virtual void visitModelFieldExecutorClaim(IModelFieldExecutorClaim *f) override { }

	virtual void visitModelFieldPool(IModelFieldPool *f) override { }

public:

    void ret(vsc::IAccept *ret) { m_core.ret(ret); }

    vsc::IAccept *get_copy(vsc::IAccept *s) {
        return m_core.get_copy(s);
    }

	template <class T> T *get_copyT(vsc::IAccept *s) {
		return dynamic_cast<T *>(get_copy(s));
	}

    void add_copy(vsc::IAccept *s, vsc::IAccept *c) {
        m_core.add_copy(s, c);
    }

protected:
    static vsc::IDebug                      *m_dbg;
    IContext                                *m_ctxt;
    IModelBuildContext                      *m_build_ctxt;
    ModelBuildContext                       m_build_ctxt_l;
    vsc::CopyVisitor                        m_core;

};

vsc::IDebug *CopyVisitor::m_dbg = 0;

}
}
}


