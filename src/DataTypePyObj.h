/**
 * DataTypePyObj.h
 *
 * Copyright 2023 Matthew Ballance and Contributors
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
#include "zsp/arl/dm/IContext.h"
#include "zsp/arl/dm/IDataTypePyObj.h"
#include "DataTypeArl.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypePyObj : 
    public virtual IDataTypePyObj,
    public virtual DataTypeArl {
public:
    DataTypePyObj(IContext *ctxt);

    virtual ~DataTypePyObj();

    virtual void initVal(vsc::dm::ValRef &v) override;

    virtual void finiVal(vsc::dm::ValRef &v) override;

    virtual vsc::dm::ValRef copyVal(const vsc::dm::ValRef &src) override;

	virtual vsc::dm::IModelField *mkRootField(
		vsc::dm::IModelBuildContext		*ctxt,
		const std::string			&name,
		bool						is_ref) override;

	virtual vsc::dm::IModelField *mkTypeField(
		vsc::dm::IModelBuildContext		*ctxt,
		vsc::dm::ITypeField				*type,
        const vsc::dm::ValRef           &val) override;

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    IContext                *m_ctxt;

};

}
}
}


