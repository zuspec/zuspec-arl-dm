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
	IContext *ctxt_a = dynamic_cast<IContext *>(ctxt->ctxt());
	IDataTypeActivityTraverse *type_t = dynamic_cast<IDataTypeActivityTraverse *>(type->getDataType());

	// TODO: resolve the type reference
	// TODO: build the expression model (if applicable)

	vsc::IModelField *target = vsc::TaskResolveFieldRefExpr(ctxt).resolve(type_t->getTarget());
	IModelFieldAction *target_a = dynamic_cast<IModelFieldAction *>(target);

	fprintf(stdout, "target=%p target_a=%p\n", target, target_a);

	IModelActivityTraverse *ret = ctxt_a->mkModelActivityTraverse(
		target_a,
		0
	);

	return ret;
}

void DataTypeActivityTraverse::accept(vsc::IVisitor *v) {
	if (dynamic_cast<arl::IVisitor *>(v)) {
		dynamic_cast<arl::IVisitor *>(v)->visitDataTypeActivityTraverse(this);
	}
}

} /* namespace arl */
