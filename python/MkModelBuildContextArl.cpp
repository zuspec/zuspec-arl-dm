
#include "arl/impl/ModelBuildContext.h"

extern "C" arl::IModelBuildContext *mkModelBuildContextArl(arl::IContext *ctxt) {
    return new arl::ModelBuildContext(ctxt);
}
