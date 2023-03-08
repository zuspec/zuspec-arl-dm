/**
 * TypeModelDumperJSON.h
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
#include <iostream>
#include <map>
#include <vector>
#include "dmgr/IDebugMgr.h"
#include "nlohmann/json_fwd.hpp"
#include "zsp/arl/dm/ITypeModelDumper.h"
#include "zsp/arl/dm/impl/VisitorBase.h"

namespace zsp {
namespace arl {
namespace dm {



class TypeModelDumperJSON :
    public virtual ITypeModelDumper,
    public virtual VisitorBase {
public:
    TypeModelDumperJSON(
        dmgr::IDebugMgr     *dmgr,
        std::ostream        *out,
        int32_t             indent);

    virtual ~TypeModelDumperJSON();

    virtual bool dumpTypeModel(
        const std::vector<vsc::dm::IAccept *> &types) override;

	virtual void visitDataTypeAction(IDataTypeAction *i) override;

	virtual void visitDataTypeActivityBind(IDataTypeActivityBind *t) override;

	virtual void visitDataTypeActivityParallel(IDataTypeActivityParallel *t) override;

	virtual void visitDataTypeActivityReplicate(IDataTypeActivityReplicate *t) override;

	virtual void visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) override;

	virtual void visitDataTypeActivitySequence(IDataTypeActivitySequence *t) override;

	virtual void visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) override;

	virtual void visitDataTypeComponent(IDataTypeComponent *t) override;

	virtual void visitDataTypeEnum(vsc::dm::IDataTypeEnum *t) override;

	virtual void visitDataTypeFunction(IDataTypeFunction *t) override;

	virtual void visitDataTypeFunctionParamDecl(IDataTypeFunctionParamDecl *t) override;

	virtual void visitDataTypeInt(vsc::dm::IDataTypeInt *t) override;

	virtual void visitDataTypeStruct(IDataTypeStruct *t) override;

	virtual void visitTypeConstraintBlock(vsc::dm::ITypeConstraintBlock *c) override;

	virtual void visitTypeConstraintExpr(vsc::dm::ITypeConstraintExpr *c) override;

	virtual void visitTypeConstraintIfElse(vsc::dm::ITypeConstraintIfElse *c) override;

	virtual void visitTypeConstraintImplies(vsc::dm::ITypeConstraintImplies *c) override;

	virtual void visitTypeConstraintScope(vsc::dm::ITypeConstraintScope *c) override;

	virtual void visitTypeConstraintSoft(vsc::dm::ITypeConstraintSoft *c) override;

	virtual void visitTypeConstraintUnique(vsc::dm::ITypeConstraintUnique *c) override;

	virtual void visitTypeExprBin(vsc::dm::ITypeExprBin *e) override;

	virtual void visitTypeExprFieldRef(vsc::dm::ITypeExprFieldRef *e) override;

	virtual void visitTypeExprRange(vsc::dm::ITypeExprRange *e) override;

	virtual void visitTypeExprRangelist(vsc::dm::ITypeExprRangelist *e) override;

	virtual void visitTypeExprVal(vsc::dm::ITypeExprVal *e) override;

	virtual void visitTypeFieldActivity(ITypeFieldActivity *f) override;

	virtual void visitTypeFieldPhy(vsc::dm::ITypeFieldPhy *f) override;

	virtual void visitTypeFieldRef(vsc::dm::ITypeFieldRef *f) override;

	virtual void visitTypeFieldVec(vsc::dm::ITypeFieldVec *f) override;

	virtual void visitTypeProcStmtAssign(ITypeProcStmtAssign *s) override;

private:
    int32_t getTypeIdx(vsc::dm::IAccept *t);

    int32_t addType(vsc::dm::IAccept *t, const nlohmann::json &jt);

    void visitExpr(nlohmann::json &jr, vsc::dm::ITypeExpr *e);

    void visitConstraint(nlohmann::json &jr, vsc::dm::ITypeConstraint *c);

private:
    static dmgr::IDebug                         *m_dbg;
    std::ostream                                *m_out;
    int32_t                                     m_indent;
    std::map<vsc::dm::IAccept *, int32_t>       m_type_m;
    int32_t                                     m_type_id;
    nlohmann::json                              *m_types;
    std::vector<nlohmann::json *>               m_json_s;
    nlohmann::json                              *m_active;
    int32_t                                     m_exec_depth;
};

}
}
}


