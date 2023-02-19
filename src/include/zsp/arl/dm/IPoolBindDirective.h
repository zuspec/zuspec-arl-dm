
#pragma once
#include <memory>
#include "vsc/dm/ITypeExprFieldRef.h"

namespace zsp {
namespace arl {
namespace dm {


enum class PoolBindKind {
	All,
	Ref
};

class IPoolBindDirective;
using IPoolBindDirectiveUP=vsc::dm::UP<IPoolBindDirective>;
class IPoolBindDirective {
public:

    virtual ~IPoolBindDirective() { }

    virtual PoolBindKind kind() const = 0;

    virtual vsc::dm::ITypeExprFieldRef *getPool() const = 0;

    virtual vsc::dm::ITypeExprFieldRef *getTarget() const = 0;

};

}
}
}
