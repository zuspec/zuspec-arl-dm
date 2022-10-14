/**
 * Marker.h
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
#include "arl/IMarker.h"

namespace arl {

class Marker : public virtual IMarker {
public:
    Marker(
        vsc::IAccept        *target,
        MarkerSeverity      severity,
        const std::string   &message
    );

    virtual ~Marker();

    virtual vsc::IAccept *getTarget() const override {
        return m_target;
    }

    virtual MarkerSeverity getSeverity() const override {
        return m_severity;
    }

    virtual const std::string &getMessage() const override {
        return m_message;
    }

private:
    vsc::IAccept                *m_target;
    MarkerSeverity              m_severity;
    std::string                 m_message;
};

}


