/*
 * DataTypeActivityTraverse.cpp
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#include "arl/IContext.h"
#include "arl/IDataTypeActivityTraverse.h"
#include "arl/IVisitor.h"
#include "vsc/IModelBuildContext.h"
#include "vsc/impl/TaskResolveFieldRefExpr.h"
#include "DataTypeActivityTraverse.h"
#include "TaskBuildModelConstraint.h"

namespace arl {

DataTypeActivityTraverse::DataTypeActivityTraverse(
		vsc::ITypeExprFieldRef 		*target,
		vsc::ITypeConstraint		*with_c) : m_target(target), m_with_c(with_c) {
	// TODO Auto-generated constructor stub

}

DataTypeActivityTraverse::~DataTypeActivityTraverse() {
	// TODO Auto-generated destructor stub
}

IModelActivity *DataTypeActivityTraverse::mkActivity(
		vsc::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) {
	IModelBuildContext *ctxt_a = dynamic_cast<IModelBuildContext *>(ctxt);
	IDataTypeActivityTraverse *type_t = dynamic_cast<IDataTypeActivityTraverse *>(type->getDataType());

	// TODO: resolve the type reference
	// TODO: build the expression model (if applicable)

	vsc::IModelField *target = vsc::TaskResolveFieldRefExpr(ctxt).resolve(type_t->getTarget());
	IModelFieldAction *target_a = dynamic_cast<IModelFieldAction *>(target);
	vsc::IModelConstraint *with_c = 0;

	fprintf(stdout, "target=%p target_a=%p\n", target, target_a);

	if (!target_a) {
		throw "Error";
	}

	if (type_t->getWithC()) {
		with_c = TaskBuildModelConstraint(ctxt_a).build(type_t->getWithC());
	}

	fprintf(stdout, "DataTypeActivity::mkActivity with_c=%p (%p)\n", type_t->getWithC(), with_c);

	IModelActivityTraverse *ret = ctxt_a->ctxt()->mkModelActivityTraverse(
		target_a,
		with_c
	);

	return ret;
}

void DataTypeActivityTraverse::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitDataTypeActivityTraverse(this);
	}
}

} /* namespace arl */
