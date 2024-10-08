/**
 * DataTypeActivityReplicate.h
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
#include "zsp/arl/dm/IDataTypeActivityReplicate.h"
#include "DataTypeActivityScope.h"

namespace zsp {
namespace arl {
namespace dm {


class DataTypeActivityReplicate : 
    public virtual IDataTypeActivityReplicate, 
    public virtual DataTypeActivityScope {
public:
    DataTypeActivityReplicate(
        IContext            *ctxt,
        vsc::dm::ITypeExpr      *count);

    virtual ~DataTypeActivityReplicate();

    virtual vsc::dm::ITypeExpr *getCount() const override {
        return m_count;
    }

	virtual IModelActivity *mkActivity(
		vsc::dm::IModelBuildContext		*ctxt,
		ITypeFieldActivity			*type) override;

    virtual vsc::dm::IDataTypeStruct *getSuper() override {
        return 0;
    }

    virtual void setSuper(vsc::dm::IDataTypeStruct *t, bool owned=false) override { }

    virtual void accept(vsc::dm::IVisitor *v) override;

private:
    vsc::dm::ITypeExpr                    *m_count;

};

}
}
}
