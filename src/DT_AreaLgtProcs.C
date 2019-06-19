#include <stdio.h>
#include "DT_AreaLgtProcs.h"

DT_AreaLgtProcs::DT_AreaLgtProcs() {};
DT_AreaLgtProcs::~DT_AreaLgtProcs() {};

void DT_AreaLgtProcs::setLgtPrim(DT_AreaLgtPrim *prm) {
    lgtPrim = prm;
}

DT_LgtPrim *DT_AreaLgtProcs::getLgtPrim() {
   return lgtPrim;
}
