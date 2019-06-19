#include "DT_LgtProcs.h"

DT_LgtProcs::DT_LgtProcs() { }
DT_LgtProcs::~DT_LgtProcs() { }

void DT_LgtProcs::setLgtPrim(DT_LgtPrim *prm) {
    lgtPrim = prm;
}

DT_LgtPrim *DT_LgtProcs::getLgtPrim() {
   return lgtPrim;
}
