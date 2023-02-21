/**
 * TypeExecTargetTmpl.h
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
#include "TypeExec.h"
#include "zsp/arl/dm/ITypeExecTargetTmpl.h"

namespace zsp {
namespace arl {
namespace dm {



class TypeExecTargetTmpl : 
    public virtual ITypeExecTargetTmpl,
    public virtual TypeExec {
public:
    TypeExecTargetTmpl(
        ExecKindT           kind,
        const std::string   &tmpl);

    virtual ~TypeExecTargetTmpl();

    virtual const std::string &getTemplate() const override {
        return m_template;
    }

    virtual void addReplacement(
        int32_t             start,
        int32_t             end,
        vsc::dm::ITypeExpr  *expr) override;

    virtual const std::vector<TypeExecTargetTmplReplacement> &getReplacements() const override {
        return m_replacements;
    }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    std::string                                         m_template;
    std::vector<TypeExecTargetTmplReplacement>          m_replacements;
    std::vector<vsc::dm::ITypeExprUP>                   m_expr_u;
};

}
}
}


