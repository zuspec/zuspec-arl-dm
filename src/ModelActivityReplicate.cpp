/*
 * ModelActivityReplicate.cpp
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
#include "arl/IVisitor.h"
#include "vsc/IDataTypeInt.h"
#include "ModelActivityReplicate.h"


namespace zsp {
namespace arl {
namespace dm {



ModelActivityReplicate::ModelActivityReplicate(
    IContext            *ctxt,
    vsc::IModelExpr     *count) : 
        ModelActivityScope(ModelActivityScopeT::Replicate), m_count_expr(count) {

/*
    vsc::IDataTypeInt *ui16 = ctxt->findDataTypeInt(false, 16);
    if (!ui16) {
        ui16 = ctxt->mkDataTypeInt(false, 16);
        ctxt->addDataTypeInt(ui16);
    }

    m_count_field = ctxt->mkModelFieldRoot(ui16, "__count");
    m_count_field->setFlags(vsc::ModelFieldFlag::DeclRand);
    addField(m_count_field);

    m_index_field = ctxt->mkModelFieldRoot(ui16, "__index");
    addField(m_index_field);
 */
}

ModelActivityReplicate::~ModelActivityReplicate() {

}

void ModelActivityReplicate::accept(vsc::IVisitor *v) {
    if (dynamic_cast<IVisitor *>(v)) {
        dynamic_cast<IVisitor *>(v)->visitModelActivityReplicate(this);
    }
}

}
}
}
