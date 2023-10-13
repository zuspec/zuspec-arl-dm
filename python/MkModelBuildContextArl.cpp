
#include "zsp/arl/dm/impl/ModelBuildContext.h"
#include "MkModelBuildContextArl.h"

zsp::arl::dm::IModelBuildContext *mkModelBuildContextArl(zsp::arl::dm::IContext *ctxt) {
    return new zsp::arl::dm::ModelBuildContext(ctxt);
}

namespace zsp {
namespace arl {
namespace dm {


}
}
}

