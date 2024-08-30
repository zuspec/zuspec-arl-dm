/*
 * DataTypeActivityTraverse.cpp
 *
 *  Created on: Jun 5, 2022
 *      Author: mballance
 */

#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IDataTypeActivityTraverse.h"
#include "zsp/arl/dm/IVisitor.h"
#include "vsc/dm/IModelBuildContext.h"
#include "vsc/dm/impl/TaskResolveFieldRefExpr.h"
#include "DataTypeActivityTraverse.h"
#include "TaskBuildModelConstraint.h"

namespace zsp {
namespace arl {
namespace dm {


DataTypeActivityTraverse::DataTypeActivityTraverse(
		vsc::dm::ITypeExpr 		        *target,
		vsc::dm::ITypeConstraint		*with_c) : m_target(target), m_with_c(with_c) {
	// TODO Auto-generated constructor stub

}

DataTypeActivityTraverse::~DataTypeActivityTraverse() {
	// TODO Auto-generated destructor stub
}

IModelActivity *DataTypeActivityTraverse::mkActivity(
		vsc::dm::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) {
	IModelBuildContext *ctxt_a = dynamic_cast<IModelBuildContext *>(ctxt);
	IDataTypeActivityTraverse *type_t = dynamic_cast<IDataTypeActivityTraverse *>(type->getDataType());

	// TODO: resolve the type reference
	// TODO: build the expression model (if applicable)

	vsc::dm::IModelField *target = vsc::dm::TaskResolveFieldRefExpr(ctxt).resolve(type_t->getTarget());
	IModelFieldAction *target_a = dynamic_cast<IModelFieldAction *>(target);
	vsc::dm::IModelConstraint *with_c = 0;

	if (!target_a) {
		throw "Error";
	}

	if (type_t->getWithC()) {
		with_c = TaskBuildModelConstraint(ctxt_a).build(type_t->getWithC());
	}

	IModelActivityTraverse *ret = ctxt_a->ctxt()->mkModelActivityTraverse(
		target_a,
		with_c,
		true,
		target_a->getActivity(),
		false
	);

	return ret;
}

void DataTypeActivityTraverse::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<arl::dm::IVisitor *>(v)) {
		dynamic_cast<arl::dm::IVisitor *>(v)->visitDataTypeActivityTraverse(this);
	}
}

}
}
}
