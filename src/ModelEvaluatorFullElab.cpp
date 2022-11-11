/*
 * ModelEvaluatorFullElab.cpp
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
#include "vsc/impl/DebugMacros.h"
#include "ModelEvaluatorFullElab.h"
#include "ModelEvaluatorFullElabActivity.h"
#include "ModelEvaluatorFullElabScope.h"
#include "TaskElaborateActivity.h"


namespace arl {


ModelEvaluatorFullElab::ModelEvaluatorFullElab(IContext *ctxt) : m_ctxt(ctxt) {
    DEBUG_INIT("ModelEvaluatorFullElab", ctxt->getDebugMgr());

}

ModelEvaluatorFullElab::~ModelEvaluatorFullElab() {

}

IModelEvalIterator *ModelEvaluatorFullElab::eval(
        const vsc::IRandState           *randstate,
        IModelFieldComponent            *root_comp,
        IDataTypeAction                 *root_action) {
    ElabActivity *exec_activity = TaskElaborateActivity(m_ctxt).elaborate(
        root_comp,
        root_action);

    return new ModelEvaluatorFullElabScope(
        m_ctxt, 
        randstate->clone(),
        exec_activity->root);
}

vsc::IDebug *ModelEvaluatorFullElab::m_dbg = 0;

}
