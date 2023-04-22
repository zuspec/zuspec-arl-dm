/*
 * TypeFieldPool.cpp
 *
 *  Created on: May 12, 2022
 *      Author: mballance
 */

#include "TypeFieldPool.h"
#include "zsp/arl/dm/IVisitor.h"

namespace zsp {
namespace arl {
namespace dm {


TypeFieldPool::TypeFieldPool(
		IContext					*ctxt,
		const std::string			&name,
		vsc::dm::IDataType				*type,
		bool						own,
		vsc::dm::TypeFieldAttr			attr,
		int32_t						decl_size) : TypeField(name, 0, false, attr),
			m_pool_t(type), m_pool_t_u((own)?type:0),
            m_decl_size(decl_size) {
	vsc::dm::IDataTypeInt *i32_t = ctxt->findDataTypeInt(true, 32);
	if (!i32_t) {
		i32_t = ctxt->mkDataTypeInt(true, 32);
		ctxt->addDataTypeInt(i32_t);
	}

	vsc::dm::IDataTypeStruct *pool_t = ctxt->mkDataTypeStruct(name + "_pool_t");
	vsc::dm::IModelValUP val(ctxt->mkModelVal());
	val->setBits(32);
	val->set_val_i(decl_size);
	pool_t->addField(ctxt->mkTypeFieldPhy(
		"size",
		i32_t,
		false,
		vsc::dm::TypeFieldAttr::NoAttr,
		val.release()));
	setDataType(pool_t, true);
}

TypeFieldPool::~TypeFieldPool() {
	// TODO Auto-generated destructor stub
}

vsc::dm::IModelField *TypeFieldPool::mkModelField(
		vsc::dm::IModelBuildContext 			*ctxt) {
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
	IModelFieldPool *pool = ctxt_a->mkModelFieldPoolType(this);

	pool->setDataTypePool(m_pool_t);

	// Fill in details
	for (std::vector<vsc::dm::ITypeFieldUP>::const_iterator
		it=getDataTypeT<vsc::dm::IDataTypeStruct>()->getFields().begin();
		it!=getDataTypeT<vsc::dm::IDataTypeStruct>()->getFields().end(); it++) {
		pool->addField((*it)->mkModelField(ctxt));
	}

	return pool;
}

void TypeFieldPool::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<arl::dm::IVisitor *>(v)) {
		dynamic_cast<arl::dm::IVisitor *>(v)->visitTypeFieldPool(this);
	} else if (v->cascade()) {
		v->visitTypeField(this);
	}
}

}
}
}
