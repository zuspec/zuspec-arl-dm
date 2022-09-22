
#pragma once
#include <memory>
#include "vsc/ITypeExprFieldRef.h"

namespace arl {

enum class PoolBindKind {
	All,
	Ref
};

class IPoolBindDirective;
using IPoolBindDirectiveUP=std::unique_ptr<IPoolBindDirective>;
class IPoolBindDirective {
public:

    virtual ~IPoolBindDirective() { }

    virtual PoolBindKind kind() const = 0;

    virtual vsc::ITypeExprFieldRef *getPool() const = 0;

    virtual vsc::ITypeExprFieldRef *getTarget() const = 0;

};

}
