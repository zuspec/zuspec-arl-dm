/*
 * TestJsonDumper.cpp
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
#include <sstream>
#include "TestJsonDumper.h"


namespace zsp {
namespace arl {
namespace dm {


TestJsonDumper::TestJsonDumper() {

}

TestJsonDumper::~TestJsonDumper() {

}

TEST_F(TestJsonDumper, smoke) {
    std::stringstream out;

    vsc::dm::IDataTypeIntUP int32(m_ctxt->mkDataTypeInt(true, 32));
    vsc::dm::IDataTypeIntUP uint16(m_ctxt->mkDataTypeInt(true, 16));

    ITypeModelDumperUP dumper(m_arl_dm_factory->mkTypeModelDumperJSON(&out, 2));
    vsc::dm::IDataTypeStructUP my_s(m_ctxt->mkDataTypeStruct("my_s"));
    my_s->addField(m_ctxt->mkTypeFieldPhy("f1", int32.get(), false, 
        vsc::dm::TypeFieldAttr::NoAttr, vsc::dm::ValRef()));
    my_s->addField(m_ctxt->mkTypeFieldPhy("f2", uint16.get(), false, 
        vsc::dm::TypeFieldAttr::NoAttr, vsc::dm::ValRef()));

    dumper->dumpTypeModel({my_s.get()});

    out.flush();
    fprintf(stdout, "Result:\n%s\n", out.str().c_str());
}

TEST_F(TestJsonDumper, actions_root_comp) {
    std::stringstream out;

    IDataTypeActionUP action1_t(m_ctxt->mkDataTypeAction("action1_t"));
    IDataTypeActionUP action2_t(m_ctxt->mkDataTypeAction("action2_t"));
    IDataTypeComponentUP comp_t(m_ctxt->mkDataTypeComponent("comp_t"));

    comp_t->addActionType(action1_t.get());
    comp_t->addActionType(action2_t.get());

    ITypeModelDumperUP dumper(m_arl_dm_factory->mkTypeModelDumperJSON(&out, 2));

    dumper->dumpTypeModel({comp_t.get()});

    out.flush();
    fprintf(stdout, "Result:\n%s\n", out.str().c_str());
}

TEST_F(TestJsonDumper, actions_root_comp_activity) {
    std::stringstream out;
    enableDebug(true);

    IDataTypeActionUP action1_t(m_ctxt->mkDataTypeAction("action1_t"));
    IDataTypeActionUP action2_t(m_ctxt->mkDataTypeAction("action2_t"));
    IDataTypeComponentUP comp_t(m_ctxt->mkDataTypeComponent("comp_t"));

    comp_t->addActionType(action1_t.get());
    comp_t->addActionType(action2_t.get());

    action1_t->addActivity(m_ctxt->mkTypeFieldActivity(
        "", 
        m_ctxt->mkDataTypeActivityTraverse(
            m_ctxt->mkTypeExprFieldRef(
                vsc::dm::ITypeExprFieldRef::RootRefKind::TopDownScope,
                0,
                {1}
            ),
            0),
            true
        ));

    ITypeModelDumperUP dumper(m_arl_dm_factory->mkTypeModelDumperJSON(&out, 2));

    dumper->dumpTypeModel({comp_t.get()});

    out.flush();
    fprintf(stdout, "Result:\n%s\n", out.str().c_str());
}

TEST_F(TestJsonDumper, actions_root_comp_action) {
    std::stringstream out;

    IDataTypeActionUP action1_t(m_ctxt->mkDataTypeAction("action1_t"));
    IDataTypeActionUP action2_t(m_ctxt->mkDataTypeAction("action2_t"));
    IDataTypeComponentUP comp_t(m_ctxt->mkDataTypeComponent("comp_t"));

    comp_t->addActionType(action1_t.get());
    comp_t->addActionType(action2_t.get());

    ITypeModelDumperUP dumper(m_arl_dm_factory->mkTypeModelDumperJSON(&out, 2));

    // Ensure that we have to think about comp_t early
    dumper->dumpTypeModel({action1_t.get(), comp_t.get()});

    out.flush();
    fprintf(stdout, "Result:\n%s\n", out.str().c_str());
}

}
}
}
