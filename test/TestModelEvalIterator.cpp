/*
 * TestModelEvalIterator.cpp
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
#include "arl/IModelFieldComponent.h"
#include "arl/impl/ModelBuildContext.h"
#include "TestModelEvalIterator.h"
#include "ModelFieldActionRoot.h"
#include "ModelActivityParallel.h"
#include "ModelActivitySequence.h"
#include "ModelActivityTraverse.h"

#include "ArlImpl.h"
#include "DebugMgr.h"
#include "RandState.h"
#include "ModelEvaluatorSequence.h"
#include "ModelEvaluatorThread.h"
#include "ModelFieldComponentRoot.h"
#include "VscImpl.h"


namespace arl {
TestModelEvalIterator::TestModelEvalIterator() {

}

TestModelEvalIterator::~TestModelEvalIterator() {

}

TEST_F(TestModelEvalIterator, two_branch_parallel) {

    // ModelAction
    // - Activity
    //   - parallel
    //     - traverse
    //     - traverse

    ArlImpl::inst()->init(vsc::DebugMgr::inst());
    IContextUP ctxt(ArlImpl::inst()->mkContext(vsc::VscImpl::inst()->mkContext()));

    IDataTypeActionUP action_t(ctxt->mkDataTypeAction("action_t"));
    IDataTypeComponentUP comp_t(ctxt->mkDataTypeComponent("comp_t"));
    action_t->setComponentType(comp_t.get());
    comp_t->addActionType(action_t.get());

    IDataTypeActionUP entry_t(ctxt->mkDataTypeAction("entry_t"));
    entry_t->addField(ctxt->mkTypeFieldPhy("a1", action_t.get(), false, vsc::TypeFieldAttr::NoAttr, 0));
    entry_t->addField(ctxt->mkTypeFieldPhy("a2", action_t.get(), false, vsc::TypeFieldAttr::NoAttr, 0));
    entry_t->setComponentType(comp_t.get());
    comp_t->addActionType(entry_t.get());

    ModelBuildContext build_ctxt(ModelBuildContext(ctxt.get()));
    IModelFieldComponentUP comp(comp_t->mkRootFieldT<IModelFieldComponent>(
        &build_ctxt,
        "pss_top",
        false));


    IDataTypeActivitySequence *activity = ctxt->mkDataTypeActivitySequence();
    vsc::ITypeExprFieldRef *ref = ctxt->mkTypeExprFieldRef();
    ref->addIdxRef(1);
    ref->addRootRef();
    activity->addActivity(ctxt->mkTypeFieldActivity(
        "",
        ctxt->mkDataTypeActivityTraverse(
            ref,
            0),
        true));

    ref = ctxt->mkTypeExprFieldRef();
    ref->addIdxRef(2);
    ref->addRootRef();
    activity->addActivity(ctxt->mkTypeFieldActivity(
        "",
        ctxt->mkDataTypeActivityTraverse(
            ref,
            0),
        true));

    entry_t->addActivity(ctxt->mkTypeFieldActivity("activity", activity, true));

    IModelFieldActionUP entry(entry_t->mkRootFieldT<IModelFieldAction>(
        &build_ctxt,
        "entry",
        false));

    vsc::IRandStateUP rs(new vsc::RandState("0"));

    IModelFieldComponentUP pss_top(comp_t->mkRootFieldT<IModelFieldComponent>(
        &build_ctxt,
        "pss_top", 
        false));
    pss_top->initCompTree();

    // IModelActivitySequence *activity = new ModelActivitySequence("", 0);
    // IModelActivityParallel *parallel = new ModelActivityParallel();
    // parallel->addBranch(new ModelActivityTraverse(traverse_1.get(), 0));
    // parallel->addBranch(new ModelActivityTraverse(traverse_2.get(), 0));
    // activity->addActivity(parallel);
    // root->addActivity(activity);

    ModelEvaluatorThread *root_thread = new ModelEvaluatorThread(
        ctxt.get(), rs->next());
    root_thread->pushComponent(comp.get());
    ModelEvaluatorSequence *root_seq = new ModelEvaluatorSequence(root_thread);
    root_seq->addActivity(new ModelActivityTraverse(entry.get(), 0), true);
    root_thread->pushIterator(root_seq);

    ASSERT_TRUE(root_thread->next());
    ASSERT_EQ(root_thread->type(), ModelEvalNodeT::Parallel);
    IModelEvalIterator *parallel_it = root_thread->iterator();
    ASSERT_TRUE(parallel_it);

    // Before evaluating the branches, click the parent iterator
    // to remove clear the parallel iterator
    ASSERT_FALSE(root_thread->next());


    ASSERT_TRUE(parallel_it->next());
    ASSERT_EQ(parallel_it->type(), ModelEvalNodeT::Sequence);

    IModelEvalIterator *branch_it = parallel_it->iterator();
    ASSERT_TRUE(branch_it);
    ASSERT_TRUE(branch_it->next());
    ASSERT_EQ(branch_it->type(), ModelEvalNodeT::Action);
    ASSERT_FALSE(branch_it->next());

    ASSERT_TRUE(parallel_it->next());
    ASSERT_EQ(parallel_it->type(), ModelEvalNodeT::Sequence);
    branch_it = parallel_it->iterator();
    ASSERT_TRUE(branch_it);
    ASSERT_TRUE(branch_it->next());
    ASSERT_EQ(branch_it->type(), ModelEvalNodeT::Action);
    ASSERT_FALSE(branch_it->next());

    ASSERT_FALSE(parallel_it->next());
}

// TEST_F(TestModelEvalIterator, two_branch_parallel_branch_seq) {

//     // ModelAction
//     // - Activity
//     //   - parallel
//     //     - traverse
//     //     - traverse

//     ArlImpl::inst()->init(vsc::DebugMgr::inst());
//     vsc::DebugMgr::inst()->enable(true);

//     IModelFieldActionUP traverse_1(new ModelFieldActionRoot("traverse_1", 0));
//     IModelFieldActionUP traverse_2(new ModelFieldActionRoot("traverse_2", 0));
//     IModelFieldActionUP root(new ModelFieldActionRoot("root", 0));

//     vsc::IRandStateUP rs(new vsc::RandState("0"));

//     IModelActivitySequence *activity = new ModelActivitySequence("", 0);
//     IModelActivityParallel *parallel = new ModelActivityParallel();
//     IModelActivitySequence *seq_1 = new ModelActivitySequence("XX", 0);
//     IModelActivitySequence *seq_2 = new ModelActivitySequence("XX", 0);

//     seq_1->addActivity(new ModelActivityTraverse(traverse_1.get(), 0));
//     seq_2->addActivity(new ModelActivityTraverse(traverse_2.get(), 0));

//     parallel->addBranch(seq_1);
//     parallel->addBranch(seq_2);
//     activity->addActivity(parallel);
//     root->addActivity(activity);

//     ModelEvaluatorThread *root_thread = new ModelEvaluatorThread(0, rs->next());
//     ModelEvaluatorSequence *root_seq = new ModelEvaluatorSequence(root_thread);
//     root_seq->addActivity(new ModelActivityTraverse(root.get(), 0), true);
//     root_thread->pushIterator(root_seq);

//     ASSERT_TRUE(root_thread->next());
//     ASSERT_EQ(root_thread->type(), ModelEvalNodeT::Parallel);
//     IModelEvalIterator *parallel_it = root_thread->iterator();
//     ASSERT_TRUE(parallel_it);

//     // Before evaluating the branches, click the parent iterator
//     // to remove clear the parallel iterator
//     ASSERT_FALSE(root_thread->next());


//     ASSERT_TRUE(parallel_it->next());
//     ASSERT_EQ(parallel_it->type(), ModelEvalNodeT::Sequence);

//     IModelEvalIterator *branch_it = parallel_it->iterator();
//     ASSERT_TRUE(branch_it);
//     ASSERT_TRUE(branch_it->next());
//     ASSERT_EQ(branch_it->type(), ModelEvalNodeT::Action);
//     ASSERT_FALSE(branch_it->next());

//     ASSERT_TRUE(parallel_it->next());
//     ASSERT_EQ(parallel_it->type(), ModelEvalNodeT::Sequence);
//     branch_it = parallel_it->iterator();
//     ASSERT_TRUE(branch_it);
//     ASSERT_TRUE(branch_it->next());
//     ASSERT_EQ(branch_it->type(), ModelEvalNodeT::Action);
//     ASSERT_FALSE(branch_it->next());

//     ASSERT_FALSE(parallel_it->next());
// }

}
