/**
 * DataTypeComponentValOpsDelegator.h
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
#include "zsp/arl/dm/IDataTypeComponent.h"
#include "DataTypeArlStructValOpsDelegator.h"

namespace zsp {
namespace arl {
namespace dm {



class DataTypeComponentValOpsDelegator : 
    public virtual IDataTypeComponent,
    public DataTypeArlStructValOpsDelegator {
public:
    DataTypeComponentValOpsDelegator(
        IContext            *ctxt,
        const std::string   &name);

    virtual ~DataTypeComponentValOpsDelegator();

	virtual const std::vector<IDataTypeAction *> &getActionTypes() const override {
        return m_action_types;
    }

	virtual void addActionType(IDataTypeAction *) override;

	virtual void addPoolBindDirective(IPoolBindDirective *bind) override {
		m_pool_binds.push_back(IPoolBindDirectiveUP(bind));
	};

	virtual const std::vector<IPoolBindDirectiveUP> &getPoolBindDirectives() const override {
		return m_pool_binds;
	}

        virtual const std::vector<ITypeFieldActivityUP> &activities() const override { 
            static std::vector<ITypeFieldActivityUP> empty;
            return empty;
        }

	virtual void addActivity(ITypeFieldActivity *activity) override { }

protected:
	std::vector<IDataTypeAction *>			        m_action_types;
	std::vector<IPoolBindDirectiveUP>		        m_pool_binds;

};

}
}
}
