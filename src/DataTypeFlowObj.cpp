/*
 * DataTypeFlowObj.cpp
 *
 *  Created on: Apr 16, 2022
 *      Author: mballance
 */
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IVisitor.h"
#include "DataTypeFlowObj.h"

namespace zsp {
namespace arl {
namespace dm {


DataTypeFlowObj::DataTypeFlowObj(
		IContext			*ctxt,
		const std::string	&name,
		FlowObjKindE 		kind) : DataTypeArlStruct(name), m_kind(kind) {
    vsc::dm::IDataTypeInt *ui32_t = ctxt->findDataTypeInt(false, 32);

    if (!ui32_t) {
        ui32_t = ctxt->mkDataTypeInt(false, 32);
        ctxt->addDataTypeInt(ui32_t);
    }

    vsc::dm::IDataTypeInt *ui1_t = ctxt->findDataTypeInt(false, 1);

    if (!ui1_t) {
        ui1_t = ctxt->mkDataTypeInt(false, 1);
        ctxt->addDataTypeInt(ui1_t);
    }

    m_poolid = ctxt->mkTypeFieldPhy(
        "pool_id",
        ui32_t,
        false,
        vsc::dm::TypeFieldAttr::Rand,
        0);
}

DataTypeFlowObj::~DataTypeFlowObj() {
	// TODO Auto-generated destructor stub
}

void DataTypeFlowObj::accept(vsc::dm::IVisitor *v) {
	if (dynamic_cast<IVisitor *>(v)) {
		dynamic_cast<IVisitor *>(v)->visitDataTypeFlowObj(this);
	} else if (v->cascade()) {
		v->visitDataTypeStruct(this);
	}
}

}
}
}
