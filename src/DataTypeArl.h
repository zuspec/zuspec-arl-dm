/**
 * DataTypeArl.h
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
#include "vsc/dm/IContext.h"
#include "vsc/dm/IDataType.h"
#include "vsc/dm/IModelField.h"

namespace zsp {
namespace arl {
namespace dm {


class DataTypeArl : 
    public virtual vsc::dm::IDataType {
public:
    DataTypeArl(int32_t bytesz=0);

    virtual ~DataTypeArl();

	// Notify datatype that no more information
	// will be added.
	virtual void finalize(vsc::dm::IContext *ctxt) override;

    virtual int32_t getByteSize() const override;

    virtual void setAssociatedData(vsc::dm::IAssociatedData *data) override;

    virtual vsc::dm::IAssociatedData *getAssociatedData() const override;

    virtual vsc::dm::IValIterator *mkValIterator(const vsc::dm::ValRef &src) override {
        return 0;
    }

    virtual vsc::dm::IValMutIterator *mkValMutIterator(const vsc::dm::ValRef &src) override {
        return 0;
    }

protected:
    int32_t                                         m_bytesz;
    vsc::dm::IAssociatedDataUP                      m_associated_data;

};

}
}
}


