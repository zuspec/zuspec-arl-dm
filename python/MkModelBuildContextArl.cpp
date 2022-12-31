
#include "zsp/arl/dm/impl/ModelBuildContext.h"

namespace zsp {
namespace arl {
namespace dm {

extern "C" IModelBuildContext *mkModelBuildContextArl(IContext *ctxt) {
    return new ModelBuildContext(ctxt);
}

}
}
}

