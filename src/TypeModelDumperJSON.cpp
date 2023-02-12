/*
 * TypeModelDumperJSON.cpp
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
#include "dmgr/impl/DebugMacros.h"
#include "TypeModelDumperJSON.h"
#include "nlohmann/json.hpp"


namespace zsp {
namespace arl {
namespace dm {


TypeModelDumperJSON::TypeModelDumperJSON(
    dmgr::IDebugMgr     *dmgr,
    std::ostream        *out,
    int32_t             indent) : m_out(out), m_indent(indent) {
    DEBUG_INIT("TypeModelDumperJSON", dmgr);
    m_type_id = 0;
}

TypeModelDumperJSON::~TypeModelDumperJSON() {

}

bool TypeModelDumperJSON::dumpTypeModel(
        const std::vector<vsc::dm::IAccept *> &types) {
    DEBUG_ENTER("dumpTypeModel");
    nlohmann::json root;
    root["type-decl"] = {};
    m_types = &root["type-decl"];
    m_active = 0;

    for (std::vector<vsc::dm::IAccept *>::const_iterator
        it=types.begin();
        it!=types.end(); it++) {
        getTypeIdx(*it);
    }

    m_json_s.pop_back();

    root["root-types"] = {};

    for (std::vector<vsc::dm::IAccept *>::const_iterator
        it=types.begin();
        it!=types.end(); it++) {
        root["root-types"].push_back(m_type_m.find(*it)->second);
    }

    *m_out << root.dump(m_indent);

    return true;
}

void TypeModelDumperJSON::visitDataTypeAction(IDataTypeAction *i) {
    DEBUG_ENTER("visitDataTypeAction %s", i->name().c_str());
    nlohmann::json type;
    type["kind"] = "data-type-action";
    type["activities"] = {};

    m_active = &type;
    VisitorBase::visitDataTypeAction(i);
    m_active = 0;

    addType(i, type);

    DEBUG_LEAVE("visitDataTypeAction %s", i->name().c_str());
}

void TypeModelDumperJSON::visitDataTypeActivityBind(IDataTypeActivityBind *t) { 

}

void TypeModelDumperJSON::visitDataTypeActivityParallel(IDataTypeActivityParallel *t) { 

}

void TypeModelDumperJSON::visitDataTypeActivityReplicate(IDataTypeActivityReplicate *t) { 

}

void TypeModelDumperJSON::visitDataTypeActivitySchedule(IDataTypeActivitySchedule *t) { 

}

void TypeModelDumperJSON::visitDataTypeActivitySequence(IDataTypeActivitySequence *t) { 
    DEBUG_ENTER("visitDataTypeActivitySequence");

    DEBUG_LEAVE("visitDataTypeActivitySequence");
}

void TypeModelDumperJSON::visitDataTypeActivityTraverse(IDataTypeActivityTraverse *t) { 
    DEBUG_ENTER("visitDataTypeActivityTraverse");
    nlohmann::json type;

    type["kind"] = "data-type-activity-traverse";
    visitExpr(type["target"], t->getTarget());

    if (m_json_s.size() == 0) {
        addType(t, type);
    } else {
        *m_json_s.back() = type;
    }

    DEBUG_LEAVE("visitDataTypeActivityTraverse");
}

void TypeModelDumperJSON::visitDataTypeComponent(IDataTypeComponent *t) {
    DEBUG_ENTER("visitDataTypeComponent %s", t->name().c_str());
    nlohmann::json type;
    type["kind"] = "data-type-component";
    type["action-types"] = {};
    m_active = &type;
    VisitorBase::visitDataTypeComponent(t);
    m_active = 0;

    // Reserve a place for us in the type map
    int32_t id = m_type_id;
    m_types->push_back(type);
    m_type_m.insert({t, id});
    m_type_id++;

    // Now, process actions that belong to this component
    nlohmann::json &action_types = m_types->at(id)["action-types"];
    for (std::vector<IDataTypeAction *>::const_iterator
        it=t->getActionTypes().begin();
        it!=t->getActionTypes().end(); it++) {
        action_types.push_back(getTypeIdx(*it));
    }

    DEBUG_LEAVE("visitDataTypeComponent %s", t->name().c_str());
}

void TypeModelDumperJSON::visitDataTypeEnum(vsc::dm::IDataTypeEnum *t) {
    nlohmann::json type;
    type["kind"] = "data-type-enum";
    type["name"] = t->name();
    type["items"] = {};

    // TODO: must be able to dump enums
//    for (std::vector<vsc::dm::IData)

    addType(t, type);
}

void TypeModelDumperJSON::visitDataTypeFunction(IDataTypeFunction *t) {
    nlohmann::json type;
    type["kind"] = "data-type-function";
    type["name"] = t->name();
    type["rtype-id"] = t->getReturnType()?getTypeIdx(t->getReturnType()):-1;
    nlohmann::json &plist = (type["plist"] = {});
    m_json_s.push_back(&plist);

    for (std::vector<IDataTypeFunctionParamDecl *>::const_iterator
        it=t->getParameters().begin();
        it!=t->getParameters().end(); it++) {
        (*it)->accept(m_this);
    }

    m_json_s.pop_back();

    nlohmann::json &body = type["body"];

    if (t->getBody()->getStatements().size()) {
        body = {};
    }
    m_json_s.push_back(&body);
    for (std::vector<ITypeProcStmtUP>::const_iterator
        it=t->getBody()->getStatements().begin();
        it!=t->getBody()->getStatements().end(); it++) {
        (*it)->accept(m_this);
    }
    
    m_json_s.pop_back();

    addType(t, type);
}

static std::map<ParamDir, std::string> param_dir_m = {
    {ParamDir::In, "in"},
    {ParamDir::Out, "out"},
    {ParamDir::InOut, "inout"}
};

void TypeModelDumperJSON::visitDataTypeFunctionParamDecl(IDataTypeFunctionParamDecl *t) {
    nlohmann::json type;

    type["name"] = t->name();
    type["type-id"] = getTypeIdx(t->getDataType());
    type["dir"] = param_dir_m.find(t->getDirection())->second;
    if (t->getInit()) {
        // TODO:
    }

    m_json_s.back()->push_back(type);
}

void TypeModelDumperJSON::visitDataTypeInt(vsc::dm::IDataTypeInt *t) {
    nlohmann::json type;
    type["kind"] = "data-type-int";
    type["is-signed"] = t->is_signed();
    type["width"] = t->width();

    addType(t, type);
}

void TypeModelDumperJSON::visitDataTypeStruct(vsc::dm::IDataTypeStruct *t) {
    bool is_root = !m_active;
    DEBUG_ENTER("visitDataTypeStruct %s (is_root=%d)", t->name().c_str(), is_root);
    nlohmann::json type;
    if (is_root) {
        m_active = &type;
        type["kind"] = "data-type-struct";
    }

    (*m_active)["name"] = t->name();
    (*m_active)["fields"] = {};
    (*m_active)["constraints"] = {};

    VisitorBase::visitDataTypeStruct(t);

    if (is_root) {
        addType(t, type);
        m_active = 0;
    }
    DEBUG_LEAVE("visitDataTypeStruct %s", t->name().c_str());
}

void TypeModelDumperJSON::visitTypeConstraintBlock(vsc::dm::ITypeConstraintBlock *c) { 
    DEBUG_ENTER("visitTypeConstraintBlock");
    nlohmann::json constraint;
    constraint["kind"] = "type-constraint-block";

    m_active = &constraint;
    VisitorBase::visitTypeConstraintBlock(c);
    m_active = 0;

    *m_json_s.back() = constraint;

    DEBUG_LEAVE("visitTypeConstraintBlock");
}

void TypeModelDumperJSON::visitTypeConstraintExpr(vsc::dm::ITypeConstraintExpr *c) { 
    DEBUG_ENTER("visitTypeConstraintExpr");
    nlohmann::json constraint;
    constraint["kind"] = "type-constraint-expr";
    visitExpr(constraint["expr"], c->expr());
    DEBUG_LEAVE("visitTypeConstraintExpr");
}

void TypeModelDumperJSON::visitTypeConstraintIfElse(vsc::dm::ITypeConstraintIfElse *c) { 
    DEBUG_ENTER("visitTypeConstraintIfElse");
    nlohmann::json constraint;
    constraint["kind"] = "type-constraint-if-else";
    visitExpr(constraint["cond"], c->getCond());
    visitConstraint(constraint["true-c"], c->getTrue());
    if (c->getFalse()) {
        visitConstraint(constraint["false-c"], c->getFalse());
    }
    DEBUG_LEAVE("visitTypeConstraintIfElse");
}

void TypeModelDumperJSON::visitTypeConstraintImplies(vsc::dm::ITypeConstraintImplies *c) { 
    DEBUG_ENTER("visitTypeConstraintImplies");
    nlohmann::json constraint;
    constraint["kind"] = "type-constraint-implies";
    visitExpr(constraint["cond"], c->getCond());
    visitConstraint(constraint["body"], c->getBody());

    DEBUG_LEAVE("visitTypeConstraintImplies");
}

void TypeModelDumperJSON::visitTypeConstraintScope(vsc::dm::ITypeConstraintScope *c) { 
    DEBUG_ENTER("visitTypeConstraintScope");
    nlohmann::json tmp;
    nlohmann::json &constraint = m_active?*m_active:tmp;

    if (!m_active) {
        constraint["kind"] = "type-constraint-scope";
    }

    nlohmann::json &constraints = (constraint["constraints"] = {});

    for (std::vector<vsc::dm::ITypeConstraintUP>::const_iterator
        it=c->getConstraints().begin();
        it!=c->getConstraints().end(); it++) {
        nlohmann::json c;
        m_json_s.push_back(&c);
        (*it)->accept(m_this);
        m_json_s.pop_back();
        constraints.push_back(c);
    }

    if (!m_active) {
        *m_json_s.back() = constraint;
    }
    DEBUG_LEAVE("visitTypeConstraintScope");
}

void TypeModelDumperJSON::visitTypeConstraintSoft(vsc::dm::ITypeConstraintSoft *c) { 
    DEBUG_ENTER("visitTypeConstraintSoft");
    nlohmann::json constraint;
    constraint["kind"] = "type-constraint-soft";
    visitConstraint(constraint["constraint"], c->constraint());
    DEBUG_LEAVE("visitTypeConstraintSoft");
}

void TypeModelDumperJSON::visitTypeConstraintUnique(vsc::dm::ITypeConstraintUnique *c) { }

static std::map<vsc::dm::BinOp, std::string> binop2str_m = {
	{ vsc::dm::BinOp::Eq, "eq" },
	{ vsc::dm::BinOp::Ne, "ne" },
	{ vsc::dm::BinOp::Gt, "gt" },
	{ vsc::dm::BinOp::Ge, "ge" },
	{ vsc::dm::BinOp::Lt, "lt" },
	{ vsc::dm::BinOp::Le, "le" },
	{ vsc::dm::BinOp::Add, "add" },
	{ vsc::dm::BinOp::Sub, "sub" },
	{ vsc::dm::BinOp::Div, "div" },
	{ vsc::dm::BinOp::Mul, "mul" },
	{ vsc::dm::BinOp::Mod, "mod" },
	{ vsc::dm::BinOp::BinAnd, "bin-and" },
	{ vsc::dm::BinOp::BinOr, "bin-or" },
	{ vsc::dm::BinOp::LogAnd, "log-and" },
	{ vsc::dm::BinOp::LogOr, "log-or" },
	{ vsc::dm::BinOp::Sll, "sll" },
	{ vsc::dm::BinOp::Srl, "srl" },
	{ vsc::dm::BinOp::Xor, "xor" },
	{ vsc::dm::BinOp::Not, "not" }
};

void TypeModelDumperJSON::visitTypeExprBin(vsc::dm::ITypeExprBin *e) { 
    DEBUG_ENTER("visitTypeExprBin");
    nlohmann::json expr;

    expr["kind"] = "type-expr-bin";

    visitExpr(expr["lhs"], e->lhs());
    expr["op"] = binop2str_m[e->op()];
    visitExpr(expr["rhs"], e->rhs());

    DEBUG_LEAVE("visitTypeExprBin");
}

static std::map<vsc::dm::ITypeExprFieldRef::RootRefKind, std::string> root_ref_kind_m = {
    {vsc::dm::ITypeExprFieldRef::RootRefKind::TopDownScope, "top-down"},
    {vsc::dm::ITypeExprFieldRef::RootRefKind::BottomUpScope, "bottom-up"}
};

void TypeModelDumperJSON::visitTypeExprFieldRef(vsc::dm::ITypeExprFieldRef *e) { 
    nlohmann::json expr;
    expr["kind"] = "type-expr-field-ref";
    expr["root-kind"] = root_ref_kind_m.find(e->getRootRefKind())->second;
    expr["root-offset"] = e->getRootRefOffset();
    nlohmann::json &path = (expr["path"] = {});

    for (std::vector<int32_t>::const_iterator
        it=e->getPath().begin();
        it!=e->getPath().end(); it++) {
        path.push_back(*it);
    }

    *m_json_s.back() = expr;
}

void TypeModelDumperJSON::visitTypeExprRange(vsc::dm::ITypeExprRange *e) { }

void TypeModelDumperJSON::visitTypeExprRangelist(vsc::dm::ITypeExprRangelist *e) { }

void TypeModelDumperJSON::visitTypeExprVal(vsc::dm::ITypeExprVal *e) { }

void TypeModelDumperJSON::visitTypeFieldActivity(ITypeFieldActivity *f) {
    DEBUG_ENTER("visitTypeFieldActivity");
    nlohmann::json field;
    field["kind"] = "type-field-activity";
    field["name"] = f->name();
    if (f->isDataTypeOwned()) {
        nlohmann::json &type = field["type"];
        m_json_s.push_back(&type);
        f->getDataType()->accept(m_this);
        m_json_s.pop_back();
    } else {
        field["type-id"] = getTypeIdx(f->getDataType());
    }

    if (m_active) {
        (*m_active)["activities"].push_back(field);
    }
    DEBUG_ENTER("visitTypeFieldActivity");
}

void TypeModelDumperJSON::visitTypeFieldPhy(vsc::dm::ITypeFieldPhy *f) {
    nlohmann::json field;
    field["kind"] = "type-field-phy";
    field["name"] = f->name();
    field["type-id"] = getTypeIdx(f->getDataType());
    
    (*m_active)["fields"].push_back(field);
}

void TypeModelDumperJSON::visitTypeFieldRef(vsc::dm::ITypeFieldRef *f) {
    nlohmann::json field;
    field["kind"] = "type-field-ref";
    field["name"] = f->name();
    field["type-id"] = getTypeIdx(f->getDataType());
    
    (*m_active)["fields"].push_back(field);
}

void TypeModelDumperJSON::visitTypeFieldVec(vsc::dm::ITypeFieldVec *f) {

}

static std::map<arl::dm::TypeProcStmtAssignOp, std::string> assign_op_m = {
    {TypeProcStmtAssignOp::Eq,      "="},
    {TypeProcStmtAssignOp::PlusEq,  "+="}, 
    {TypeProcStmtAssignOp::MinusEq, "-="},
    {TypeProcStmtAssignOp::ShlEq, "<<="},
    {TypeProcStmtAssignOp::ShrEq, ">>="},
    {TypeProcStmtAssignOp::OrEq,    "|="},
    {TypeProcStmtAssignOp::AndEq,   "&="}
};

void TypeModelDumperJSON::visitTypeProcStmtAssign(ITypeProcStmtAssign *s) {
    nlohmann::json stmt;

    stmt["kind"] = "proc-stmt-assign";
    stmt["op"] = assign_op_m.find(s->op())->second;
    visitExpr(stmt["lhs"], s->getLhs());
    visitExpr(stmt["rhs"], s->getRhs());

    m_json_s.back()->push_back(stmt);
}

int32_t TypeModelDumperJSON::getTypeIdx(vsc::dm::IAccept *t) {
    std::map<vsc::dm::IAccept *, int32_t>::const_iterator it;

    if ((it=m_type_m.find(t)) != m_type_m.end()) {
        return it->second;
    } else {
        // Actually go build it
        nlohmann::json *active_s = m_active;
        m_active = 0;
        t->accept(m_this);
        m_active = active_s;
        if ((it=m_type_m.find(t)) != m_type_m.end()) {
            return it->second;
        } else {
            fprintf(stdout, "Internal Error: failed to serialize JSON\n");
        }
    }
}

int32_t TypeModelDumperJSON::addType(vsc::dm::IAccept *t, const nlohmann::json &jt) {
    m_types->push_back(jt);
    m_type_m.insert({t, m_type_id});
    m_type_id++;
    return m_type_id-1;
}

void TypeModelDumperJSON::visitExpr(nlohmann::json &jr, vsc::dm::ITypeExpr *e) {
    m_json_s.push_back(&jr);
    e->accept(m_this);
    m_json_s.pop_back();
}

void TypeModelDumperJSON::visitConstraint(nlohmann::json &jr, vsc::dm::ITypeConstraint *c) {
    m_json_s.push_back(&jr);
    c->accept(m_this);
    m_json_s.pop_back();
}

dmgr::IDebug *TypeModelDumperJSON::m_dbg = 0;

}
}
}
