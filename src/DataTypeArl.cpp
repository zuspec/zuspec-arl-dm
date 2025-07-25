/*
 * DataTypeArl.cpp
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
#include "DataTypeArl.h"


namespace zsp {
namespace arl {
namespace dm {


DataTypeArl::DataTypeArl(int32_t bytesz) : m_bytesz(bytesz) {

}

DataTypeArl::~DataTypeArl() {

}

void DataTypeArl::finalize(vsc::dm::IContext *ctxt) {

}

int32_t DataTypeArl::getByteSize() const {
    return m_bytesz;
}

void DataTypeArl::setAssociatedData(vsc::dm::IAssociatedData *data, bool owned) {
    m_associated_data = vsc::dm::IAssociatedDataUP(data, owned);
}

vsc::dm::IAssociatedData *DataTypeArl::getAssociatedData() const {
    return m_associated_data.get();
}

}
}
}
