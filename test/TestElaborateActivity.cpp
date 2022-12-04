/*
 * TestElaborateActivity.cpp
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
#include "TestElaborateActivity.h"
#include "arl/impl/ModelBuildContext.h"
#include "TaskElaborateActivity.h"


namespace arl {


TestElaborateActivity::TestElaborateActivity() {

}

TestElaborateActivity::~TestElaborateActivity() {

}

TEST_F(TestElaborateActivity, resource_wildcard_1t_1p) {
    enableDebug(true);

    vsc::ITypeExprFieldRef *ref;
    IDataTypeFlowObjUP rsrc_t(m_ctxt->mkDataTypeFlowObj("rsrc_t", FlowObjKindE::Resource));

    // component pss_top {
    //   pool [2] rsrc_t   rsrc_p;
    // }
    // 
    IDataTypeComponentUP pss_top_t(m_ctxt->mkDataTypeComponent("pss_top"));
    pss_top_t->addField(m_ctxt->mkTypeFieldPool("rsrc_p", rsrc_t.get(), false, vsc::TypeFieldAttr::NoAttr, 2));
    ref = m_ctxt->mkTypeExprFieldRef();
    ref->addIdxRef(1);
    ref->addRootRef();
    pss_top_t->addPoolBindDirective(m_ctxt->mkPoolBindDirective(
        PoolBindKind::All,
        ref,
        0));

    // action_t
    // action action_t {
    //   lock rsrc_t   r1;
    // }
    //
    IDataTypeActionUP action1_t(m_ctxt->mkDataTypeAction("action1_t"));
    action1_t->addField(m_ctxt->mkTypeFieldClaim("l1", rsrc_t.get(), true));
    action1_t->setComponentType(pss_top_t.get());
    pss_top_t->addActionType(action1_t.get());


    // entry_t
    // action entry_t {
    //   action_t a1, a2;
    //   activity {
    //     parallel {
    //       a1;
    //       a2;
    //     }
    //  }
    IDataTypeActionUP entry_t(m_ctxt->mkDataTypeAction("entry_t"));
    entry_t->addField(m_ctxt->mkTypeFieldPhy("a1", action1_t.get(), false, vsc::TypeFieldAttr::NoAttr, 0));
    entry_t->addField(m_ctxt->mkTypeFieldPhy("a2", action1_t.get(), false, vsc::TypeFieldAttr::NoAttr, 0));
    entry_t->setComponentType(pss_top_t.get());
    pss_top_t->addActionType(entry_t.get());

    IDataTypeActivityParallel *par = m_ctxt->mkDataTypeActivityParallel();
    ref = m_ctxt->mkTypeExprFieldRef();
    ref->addIdxRef(1);
    ref->addRootRef();
    par->addActivity(m_ctxt->mkTypeFieldActivity(
        "", m_ctxt->mkDataTypeActivityTraverse(ref, 0), true));

    ref = m_ctxt->mkTypeExprFieldRef();
    ref->addIdxRef(2);
    ref->addRootRef();
    par->addActivity(m_ctxt->mkTypeFieldActivity(
        "", m_ctxt->mkDataTypeActivityTraverse(ref, 0), true));

    // Root activity is always expected to be a scope
    IDataTypeActivitySequence *activity_root = m_ctxt->mkDataTypeActivitySequence();
    activity_root->addActivity(m_ctxt->mkTypeFieldActivity(
        "", 
        par,
        true));

    entry_t->addActivity(m_ctxt->mkTypeFieldActivity(
        "activity", 
        activity_root,
        true));

    ModelBuildContext build_ctxt(m_ctxt.get());
    IModelFieldComponentRootUP pss_top(pss_top_t->mkRootFieldT<IModelFieldComponentRoot>(
        &build_ctxt,
        "pss_top", 
        false));

    pss_top->initCompTree();

    ASSERT_EQ(pss_top->getPools(rsrc_t.get()).size(), 1);
    ASSERT_EQ(pss_top->getResObjects(dynamic_cast<IDataTypeResource *>(rsrc_t.get())).size(), 2);
    std::pair<int32_t,int32_t> pool_r = pss_top->getResPoolObjRange(pss_top->getPools(rsrc_t.get()).at(0));
    ASSERT_EQ(pool_r.first, 0);
    ASSERT_EQ(pool_r.second, 1);
    ASSERT_EQ(pool_r.second, 1);
    const std::vector<std::pair<int32_t,IModelFieldPool *>> &claim_m = pss_top->getClaimBoundCompPool(
        action1_t->getFieldT<ITypeFieldClaim>(1));
    ASSERT_EQ(claim_m.size(), 1);
    ASSERT_EQ(claim_m.at(0).first, 0);

    TaskElaborateActivity(m_ctxt.get()).elaborate(
        m_randstate.get(),
        pss_top.get(),
        entry_t.get()
    );
}

}
