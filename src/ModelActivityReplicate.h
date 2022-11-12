/**
 * ModelActivityReplicate.h
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
#include "arl/IModelActivityReplicate.h"
#include "ModelActivityScope.h"

namespace arl {


class ModelActivityReplicate : 
    public virtual IModelActivityReplicate, 
    public virtual ModelActivityScope{
public:
    ModelActivityReplicate(
        IContext            *ctxt,
        vsc::IModelExpr     *count);

    virtual ~ModelActivityReplicate();

    virtual vsc::IModelExpr *getCountExpr() const override {
        return m_count_expr.get();
    }

    virtual vsc::IModelField *getCountField() const override {
        return fields().at(0).get();
    }

    virtual vsc::IModelField *getIndexField() const override {
        return m_index_field;
    }

    virtual void accept(vsc::IVisitor *v) override;

private:
    vsc::IModelExprUP                  m_count_expr;
    vsc::IModelField                   *m_count_field;
    vsc::IModelField                   *m_index_field;

};

}


