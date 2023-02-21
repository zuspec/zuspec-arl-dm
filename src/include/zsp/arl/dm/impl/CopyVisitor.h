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
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IModelBuildContext.h"
#include "zsp/arl/dm/impl/ModelBuildContext.h"
#include "zsp/arl/dm/impl/VisitorDelegator.h"
#include "vsc/dm/impl/CopyVisitor.h"
#include "dmgr/IDebugMgr.h"
#include "dmgr/impl/DebugMacros.h"

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

    vsc::dm::IAccept *copy(vsc::dm::IAccept *o) {
        return m_core.copy(o);
    }

    template <class T> T *copyT(vsc::dm::IAccept *o) {
        return dynamic_cast<T *>(copy(o));
    }

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override {

    }

	virtual void visitDataTypeFlowObj(IDataTypeFlowObj *t) override { }

	virtual void visitDataTypeFunction(IDataTypeFunction *t) override { }

	virtual void visitDataTypeResource(IDataTypeResource *t) override { }

	virtual void visitModelActivityParallel(IModelActivityParallel *a) override { }

	virtual void visitModelActivityReplicate(IModelActivityReplicate *a) override { 
        vsc::dm::IModelExpr *count_e = copyT<vsc::dm::IModelExpr>(a->getCountExpr());
        IModelActivityReplicate *ac = m_ctxt->mkModelActivityReplicate(count_e);

        for (std::vector<vsc::dm::IModelFieldUP>::const_iterator
            it=a->fields().begin();
            it!=a->fields().end(); it++) {
            ac->addField(copyT<vsc::dm::IModelField>(it->get()));
        }
        
        for (std::vector<vsc::dm::IModelConstraintUP>::const_iterator
            it=a->constraints().begin();
            it!=a->constraints().end(); it++) {
            ac->addConstraint(copyT<vsc::dm::IModelConstraint>(it->get()));
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
        vsc::dm::IModelConstraint *with_c = 0;
        if (a->getWithC()) {
            with_c = copyT<vsc::dm::IModelConstraint>(a->getWithC());
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

        for (std::vector<vsc::dm::IModelFieldUP>::const_iterator
            it=f->fields().begin();
            it!=f->fields().end(); it++) {
            fc->addField(copyT<vsc::dm::IModelField>(it->get()));
        }

        for (std::vector<vsc::dm::IModelConstraintUP>::const_iterator
            it=f->constraints().begin();
            it!=f->constraints().end(); it++) {
            fc->addConstraint(copyT<vsc::dm::IModelConstraint>(it->get()));
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

    void ret(vsc::dm::IAccept *ret) { m_core.ret(ret); }

    vsc::dm::IAccept *get_copy(vsc::dm::IAccept *s) {
        return m_core.get_copy(s);
    }

	template <class T> T *get_copyT(vsc::dm::IAccept *s) {
		return dynamic_cast<T *>(get_copy(s));
	}

    void add_copy(vsc::dm::IAccept *s, vsc::dm::IAccept *c) {
        m_core.add_copy(s, c);
    }

protected:
    static vsc::dm::IDebug                      *m_dbg;
    IContext                                *m_ctxt;
    IModelBuildContext                      *m_build_ctxt;
    ModelBuildContext                       m_build_ctxt_l;
    vsc::dm::CopyVisitor                        m_core;

};

vsc::dm::IDebug *CopyVisitor::m_dbg = 0;

}
}
}


