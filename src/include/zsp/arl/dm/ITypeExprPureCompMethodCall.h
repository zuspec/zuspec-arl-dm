/**
 * ITypeExprPureCompMethodCall.h
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

namespace zsp {
namespace arl {
namespace dm {



class ITypeExprPureCompMethodCall {
public:

    virtual ~ITypeExprPureCompMethodCall() { }

    // TODO: type path to pure-comp field
    // Note: the pure-comp root type can be inferred from this

    // TODO: path through pure-comp hierarchy
    // Note: this will be empty if the method call is on the root field

    // TODO: method index

    // TODO: method parameters

};

} /* namespace dm */
} /* namespace arl */
} /* namespace zsp */


