#include <stdio.h>
#include "DT_SpotLgtProcs.h"

DT_SpotLgtProcs::DT_SpotLgtProcs() {};
DT_SpotLgtProcs::~DT_SpotLgtProcs() {};

void DT_SpotLgtProcs::setLgtPrim(DT_SpotLgtPrim *prm) {
    lgtPrim = prm;
}

DT_LgtPrim *DT_SpotLgtProcs::getLgtPrim() {
   return lgtPrim;
}
